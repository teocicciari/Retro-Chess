# Retro chess

This is a chess program completely written from the ground in C Programming Language to be played on linux terminal.

I began to write it to strengthen my knowledge adquired in the course *Algorithms and data structures II* of my carreer, and it was improved along with my skills.

## How to Play

Clone de repository:

```
git clone https://github.com/teocicciari/chessprogram.git
```

Generate the executable:
```
make
```

Execution:
```
./chessprogram
```

Play!

## Moves

To move you need to use the [chess standard notation](https://en.wikipedia.org/wiki/Algebraic_notation_(chess)), a quick guide:

- **e4** to move a pawn (the square to get).
- **Nf3** to move the Knight to *f3*.
- Names: **Q** -> Queen, **K** -> King, **N** -> Knight, **B** -> Bishop, **R** -> Rook.
- **Nxe4** to capture a piece in e4. **exd5** in the case of a pawn.
- if, for example, two knights can go to the same square you need to include the row or column to determinate wich one you want to move: **Nbd5**, **N5d4**.
- **0-0** for castle kingside, **0-0-0** for castle queenside.
