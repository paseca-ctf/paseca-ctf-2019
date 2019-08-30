## Happy PASECA
Twin sons of my mothers uncle semi-dad who live in the near village are trying to do some gamedev. One of them, legendary Boka, is a code-writer. Second one - his popular brother Joka, is making some design solutions.
Their first game is gradually coming to the release state, so they gave us a pre-release firefox version to dome some testing. They are rewarding a, probably, some piece of cloth on a stick, if we correctly understood... Ehm, anyway, can you look into that?
## Flag
paseca{w45m_br1n65_m3_h0n3y_fr0m_7h3_7r335}
## Notes
[DEPLOY] Просто раздача статики

## WriteUp
Game tells us to "match honey and beehives in the proper order".
Open .wasm file in disassembler and look around. We see a lot of strings in binary, presumably it is compiled in debug mode.
In "imports" segment we see strings like "cargo_web_snippet...". Google it! It means that executable compiled with "cargo web".
It is written in Rust language. Try to google something like "rust webassembly game engine". The first result is "quicksilver".
There are a lot of strings with "quicksilver" in file. Gotcha! Read quicksilver docs.
Now it is pretty easy to find main logic functions, which checks proper order of honey.
Searching "update" gives us interesting function. It is very clear and useless, but note "HappyPaseca" substring.
```
func $_ZN79_$LT$wasm_game..HappyPaseca$u20$as$u20$quicksilver..lifecycle..state..State$GT$6update17h410f51e1afef93c0E (param i32 i32 i32)
(local i32 i32 i32 i32)
  global.get 0
  local.set 3
  i32.const 16
  local.set 4
  local.get 3
  local.get 4
  i32.sub
  local.set 5
  i32.const 8
  local.set 6
  local.get 5
  local.get 1
  i32.store offset=0 align=4
  local.get 5
  local.get 2
  i32.store offset=4 align=4
  local.get 0
  local.get 6
  i32.store8 offset=0 align=1
  return
end
```
Searching by it gives us all 4 main functions! Gotcha!
By debugging "event" function we have understood that after matching all honey jars it execute interesting code which "$_ZN9wasm_game12check_orders17h405c706e0b65b1a0E" function (firefox disassembly).
In that function we see "i32.xor" instruction which xor some number with constant -120 (0x88).
After debugging we have understood that this number is an order number of honey jar in the first top-left beehive.
```
block
    local.get 21
    i32.eqz
    br_if 0
    i32.const 1
    local.set 24
    local.get 23
    local.get 24
    i32.eq
    local.set 25
    block
      local.get 25
      br_if 0
      unreachable
    end
    local.get 4
    i32.load offset=52 align=4
    local.set 26
    local.get 4
    local.get 26
    i32.store offset=56 align=4
    local.get 4
    i32.load offset=56 align=4
    local.set 27
    local.get 4
    local.get 27
    i32.store offset=48 align=4
    local.get 4
    i32.load offset=48 align=4
    local.set 28
    local.get 4
    local.get 28
    i32.store offset=60 align=4
    local.get 4
    i32.load offset=60 align=4
    local.set 29
    local.get 29
    i32.load8_u offset=8 align=1
    local.set 30
    local.get 29
    i32.load8_u offset=10 align=1
    local.set 31
    i32.const -120
    local.set 32
    local.get 31
    local.get 32
    i32.xor // xor with const
    local.set 33
    i32.const 255
    local.set 34
    local.get 30
    local.get 34
    i32.and
    local.set 35
    i32.const 255
    local.set 36
    local.get 33
    local.get 36
    i32.and
    local.set 37
    local.get 35
    local.get 37
    i32.ne // comparison with constant in memory
    local.set 38
    i32.const 1
    local.set 39
    local.get 38
    local.get 39
    i32.and
    local.set 40
    local.get 40
    br_if 1
    br 2
end
```
We can modify 31 variable before xor, then this check will pass.
Next it will xor with an order number of honey jar in the second top-left beehive.
Of course we can pass this challenge by hand for all 32 beehives and it will show us flag!
Or we can get array of bytes with which xored numbers compared, xor it and get the proper order.
Also we can try to reverse function "$_ZN9wasm_game7decrypt17hd37759526648e09fE (param i32 i32 i32)" which called in event function after successful check.
