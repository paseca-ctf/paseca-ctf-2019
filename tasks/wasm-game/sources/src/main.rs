extern crate quicksilver;
extern crate hex;
extern crate aes_soft as aes;
extern crate block_modes;
extern crate num;
extern crate rand;
#[macro_use] extern crate hex_literal;

use hex::{FromHex, ToHex};
use num::BigInt;
use block_modes::{BlockMode, Cbc};
use block_modes::block_padding::Pkcs7;
use aes::Aes256;
use num::FromPrimitive;


type Aes256Cbc = Cbc<Aes256, Pkcs7>;


use quicksilver::{
    Future, Result, // We need the Future trait to operate on a future
    geom::{Rectangle, Shape, Vector, Scalar, Transform},
    graphics::{Background::Img, Color, Image, PixelFormat},
    lifecycle::{Asset, Settings, State, Window, run, Event},
    input::{Key, ButtonState, MouseButton}
};
use hex_literal::hex;
use num::{Zero, One};
use num::ToPrimitive;

use std::ops::{Add, Sub, Mul, Div, Rem, Neg};
use std::cmp::Ordering;
use std::hash::Hash;
use std::convert::From;

use rand::rngs::{StdRng, OsRng};
use rand::{RngCore, SeedableRng};
use rand::prelude::*;


const KEY: [u8; 32] = [133, 140, 142, 148, 151, 149, 134, 144, 132, 135, 130, 159, 155, 146, 141, 128, 147, 145, 150, 158, 153, 139, 137, 136, 129, 138, 157, 131, 156, 154, 143, 152];//[215, 229, 411, 114, 380, 812, 655, 34, 631, 80, 849, 274, 720, 561, 586, 584, 147, 721, 337, 140, 747, 289, 378, 378, 312, 375, 559, 389, 654, 510, 98, 687];
const MAGIC: u16 = 0x1337;
const XOR: u8 = 0x88;

const G: u16 = 747;
const M: u16 = 907;
const HIVE_SIZE: Vector = Vector{x: 70f32, y: 80f32};

fn normalize<T: Integer>(a: T, n: &T) -> T
    where for<'a> &'a T: IntegerOps<T>
{
    let a = a % n;
    match a.cmp(&T::zero()) {
        Ordering::Less => a + n,
        _ => a,
    }
}

#[derive(Debug, Copy, Clone, PartialEq, Eq)]
struct GcdResult<T> {
    /// Greatest common divisor.
    gcd: T,
    /// Coefficients such that: gcd(a, b) = c1*a + c2*b
    c1: T, c2: T,
}

/// Calculate greatest common divisor and the corresponding coefficients.
fn extended_gcd<T: Integer>(a: T, b: T) -> GcdResult<T>
    where for<'a> &'a T: IntegerOps<T>
{
    // Euclid's extended algorithm
    let (mut s, mut old_s) = (T::zero(), T::one());
    let (mut t, mut old_t) = (T::one(), T::zero());
    let (mut r, mut old_r) = (b, a);

    while r != T::zero() {
        let quotient = &old_r / &r;
        old_r = old_r - &quotient * &r; std::mem::swap(&mut old_r, &mut r);
        old_s = old_s - &quotient * &s; std::mem::swap(&mut old_s, &mut s);
        old_t = old_t - quotient * &t; std::mem::swap(&mut old_t, &mut t);
    }

    let _quotients = (t, s); // == (a, b) / gcd

    GcdResult { gcd: old_r, c1: old_s, c2: old_t }
}

/// Calculate the inverse of a (mod n).
fn inverse<T: Integer + Clone>(a: T, n: &T) -> Option<T>
    where for<'a> &'a T: IntegerOps<T>
{
    let GcdResult { gcd, c1: c, .. } = extended_gcd(a, n.clone());
    if gcd == T::one() {
        Some(normalize(c, n))
    } else {
        None
    }
}

/// Calculate base^exp (mod modulus).
fn powm(base: &BigInt, exp: &BigInt, modulus: &BigInt) -> BigInt {
    let zero = Integer::zero();
    let one: BigInt = Integer::one();
    let two = &one + &one;
    let mut exp = exp.clone();
    let mut result = one.clone();
    let mut base = base % modulus;
    if exp < zero {
        exp = -exp;
        base = inverse(base, modulus).unwrap();
    }
    while exp > zero {
        if &exp % &two == one {
            result = (result * &base) % modulus;
        }
        exp = exp >> 1;
        base = (&base * &base) % modulus;
    }
    result
}

trait IntegerValOps<RHS, Output>: Sized
+ Add<RHS, Output = Output> + Sub<RHS, Output = Output>
+ Mul<RHS, Output = Output> + Div<RHS, Output = Output>
+ Rem<RHS, Output = Output> + Neg<Output = Output> {
}

impl<RHS, Output, T> IntegerValOps<RHS, Output> for T
    where T: Sized
    + Add<RHS, Output = Output> + Sub<RHS, Output = Output>
    + Mul<RHS, Output = Output> + Div<RHS, Output = Output>
    + Rem<RHS, Output = Output> + Neg<Output = Output>
{
}

trait IntegerOps<Base>: IntegerValOps<Base, Base>
+ for<'a> IntegerValOps<&'a Base, Base> {
}

impl<Base, T> IntegerOps<Base> for T
    where T: IntegerValOps<Base, Base>
    + for<'a> IntegerValOps<&'a Base, Base>
{
}

trait Integer:
Sized + Eq + Ord + Clone
+ IntegerOps<Self>
+ From<u64> + Hash
{
    fn zero() -> Self;
    fn one() -> Self;
    fn invert(&self, modulus: &Self) -> Option<Self>;
    fn powm(&self, exp: &Self, modulus: &Self) -> Self;
}

impl Integer for BigInt {
    fn zero() -> BigInt {
        Zero::zero()
    }

    fn one() -> BigInt {
        One::one()
    }

    fn invert(&self, modulus: &BigInt) -> Option<BigInt> {
        inverse(self.clone(), modulus)
    }

    fn powm(&self, exp: &BigInt, modulus: &BigInt) -> BigInt {
        powm(self, exp, modulus)
    }
}

struct HappyPaseca {
    assets: GameAssets,

    hives: Vec<Hive>,
    jars: Vec<HoneyJar>,
    render_welcome: bool,
    render_flag: bool,
    render_noflag: bool,
    magic: u16,
    g: u16,
    m: u16,
    current_jar: u8,
}

impl State for HappyPaseca {
    fn new() -> Result<HappyPaseca> {
        let mut rng = StdRng::seed_from_u64(1);
        let mut state = HappyPaseca {
            assets: GameAssets {
                bg: load_image("bg.png"),
                welcome: load_image("welcome.png"),
                hives: vec![load_image("hive1.png"), load_image("hive2.png")],
                jars: vec![load_image("jar1.png"), load_image("jar2.png"), load_image("jar3.png")],
                flag: Image::from_raw(&[], 32, 32, PixelFormat::RGBA).unwrap(),
                noflag: load_image("neflag.png")
            },
            hives: vec![],
            jars: vec![],
            render_welcome: true,
            render_flag: false,
            render_noflag: false,
            magic: 0x1337,
            g: 747,
            m: 907,
            current_jar: 0
        };
        for i in 0u8..32 {
            let num = i as u32;

            let hive_col = (num / 8) as u32;
            let hive_row = (num % 8) as u32;
            state.hives.push(Hive {
                position: Vector::new(50 + 100 * hive_row, 50 + 100 * hive_col),
                hive_type: rng.gen_range(0, 2),
                honey_enc_id: KEY[num as usize],
                honey_jar_inside: 33
            });
            let jar_col = (num / 16) as u32;
            let jar_row = (num % 16) as u32;
            state.jars.push(HoneyJar {
                position: Vector::new(200 + 25 * jar_row, 500 + 40 * jar_col),
                id: i,
                jar_type: rng.gen_range(0, 2),
            })
        }

        Ok(state)
    }

    fn update(&mut self, _window: &mut Window) -> Result<()> {

        Ok(())
    }

    fn event(&mut self, event: &Event, window: &mut Window) -> Result<()> {
        if let Event::MouseButton(MouseButton::Left, ButtonState::Pressed) = event {
            if self.render_welcome {
                self.render_welcome = false;
                return Ok(());
            }
            let mut is_ready = true;
            for hive in &mut self.hives {
                let mut current_ready = false;
                if hive.honey_jar_inside == 33
                {
                    current_ready = false;
                    if Rectangle::new_sized(HIVE_SIZE).with_center(hive.position).contains(window.mouse().pos()) {
                        if (self.current_jar as usize) < self.jars.len() {
                            let mut new_pos = hive.position.clone();
                            new_pos.y -= 40f32;
                            self.jars[self.current_jar as usize].position = new_pos;

                            hive.honey_jar_inside = self.current_jar as u8;
                            self.current_jar += 1;
                            current_ready = true;
                        }
                    }
                }else {
                    current_ready = true;
                }
                is_ready &= current_ready;
            }

            if is_ready && !self.render_flag && !self.render_noflag{
                let key = check_orders(self);
                if key.is_some() {
                    let key_data = key.unwrap();
                    decrypt(self, key_data.as_slice());
                } else {
                    self.render_noflag = true;
                }
            }
        };
        Ok(())
    }

    fn draw(&mut self, window: &mut Window) -> Result<()> {
        window.clear(Color::WHITE)?;
        render_at_position(&mut self.assets.bg, Vector::new(400, 300), 0, window);

        if self.render_welcome {
            render_at_position(&mut self.assets.welcome, Vector::new(400, 300), 4, window);
        }

        if self.render_noflag {
            render_at_position(&mut self.assets.noflag, Vector::new(400, 300), 5, window);
        }

        if self.render_flag {
            window.draw_ex(&self.assets.flag.area().with_center(Vector::new(400, 300)), Img(&self.assets.flag), Transform::IDENTITY, 5);
        }

        for hive in &self.hives {
            render_at_position(&mut self.assets.hives[hive.hive_type as usize], hive.position, 1, window);
        }

        for jar in &self.jars {
            render_at_position(&mut self.assets.jars[jar.jar_type as usize], jar.position, 1, window);
        }

        Ok(())
    }
}

fn decrypt(paseca: &mut HappyPaseca, key: &[u8]) {
    let iv = hex!("f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff");
    let plaintext = include_bytes!("..\\static\\flag.dat");
    let cipher = Aes256Cbc::new_var(&key, &iv).unwrap();

    let decrypted_ciphertext = cipher.decrypt_vec(plaintext).unwrap();
    let flag = Image::from_bytes(decrypted_ciphertext.as_slice()).unwrap();
    paseca.assets.flag = flag;
    paseca.render_flag = true;
}


fn check_orders(paseca: &mut HappyPaseca) -> Option<Vec<u8>>
{
    let mut key = Vec::new();

    for hive in &paseca.hives {
        if hive.honey_enc_id != hive.honey_jar_inside ^ XOR {
            return  None;
        }
        key.push(hive.honey_jar_inside);
    }
    /*let mut magic = MAGIC;
    for hive in &paseca.hives {
        let pm = powm(&BigInt::from_u16(G).unwrap(), &BigInt::from_u16(magic - hive.honey_jar_inside as u16).unwrap(), &BigInt::from_u16(M).unwrap());
        let suc = BigInt::from_u16(hive.honey_enc_id).unwrap();
        if pm != suc {
            return None;
        }
        magic -= hive.honey_jar_inside as u16;
        key.push(hive.honey_jar_inside);
    }*/

    return Some(key);
}

fn main() {
    run::<HappyPaseca>("Happy PASECA", Vector::new(800, 600), Settings {
        ..Settings::default()
    });
}


fn load_image(name: &'static str) -> Asset<Image> {
    Asset::new(
        Image::load(name)
    )
}

fn render_at_position(img: &mut Asset<Image>, position: Vector, z_order: i32, window: &mut Window) {
    img.execute(|image| {
        window.draw_ex(&image.area().with_center(position), Img(&image), Transform::IDENTITY, z_order);
        Ok(())
    });
}

pub struct GameAssets {
    pub bg: Asset<Image>,
    pub welcome: Asset<Image>,
    pub hives : Vec<Asset<Image>>,
    pub jars: Vec<Asset<Image>>,
    pub flag: Image,
    pub noflag: Asset<Image>
}

pub struct Hive {
    pub position: Vector,
    pub honey_enc_id: u8,
    pub hive_type: u8,
    pub honey_jar_inside: u8
}

pub struct HoneyJar {
    pub position: Vector,
    pub id: u8,
    pub jar_type: u8
}