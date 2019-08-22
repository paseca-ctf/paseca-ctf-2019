# Total Recall
### Ready dump link
[Download](https://drive.google.com/file/d/1qcCTiGuTrN40tf8D00Br52C3fOi67WbU/view?usp=sharing)

## Description
Pun intended, nevertheless useless

We got this [dump](https://drive.google.com/file/d/1qcCTiGuTrN40tf8D00Br52C3fOi67WbU/view?usp=sharing) and need to recover extremely secret data from it

~~Send me pics of flag!~~

## How to solve/check:
* Get script from dump by searching "paseca" (part of AES key)
* Get encrypted pic from dump by finding flag_.txt opened in notepad++ first (it also contains paseca keyword + lorem ipsum)
* Find strings that go before it
* Grep for such strings inside 2nd notepad++ process memory trying to find encrypted flag.png data afterwards (aes+base64)
* Write script similiar to [solver.py](solver/solver.py)
Or you can check [solver.py](solver/solver.py) and [enc_pic](solver/enc_pic): `python3 solver.py enc_pic PNG`

# Flag
![alt text](src/flag.png "paseca{l00k_4_p4113rn57}")

#### P.S.
> I da, eto ne ya anglichanin, a shrifty russkie v arche sleteli
