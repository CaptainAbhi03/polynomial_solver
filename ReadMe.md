# Polynomial Solver from Roots

This project computes the coefficients of a polynomial given its roots in various bases.

## Problem Statement
- Input is given in JSON format with roots expressed in different bases.
- The task is to convert roots to decimal, then compute the polynomial coefficients.
- Polynomial degree = k - 1, where k roots are required.

## How to Compile & Run

```bash
g++ main.cpp -o solver
./solver

APPROACH 

We first change the given roots (which are written in different bases) into decimal numbers.
Then we multiply step by step with 
(
𝑥
−
𝑟
𝑜
𝑜
𝑡
)
(x−root) for each root.
The final expanded result gives us the polynomial coefficients.

Testcase 1
Roots → 4 (base 10), 111 (base 2 = 7), 12 (base 10)
Polynomial → 
(
𝑥
−
4
)
(
𝑥
−
7
)
(
𝑥
−
12
)
=
𝑥
3
−
23
𝑥
2
+
160
𝑥
−
336
(x−4)(x−7)(x−12)=x
3
−23x
2
+160x−336
Coefficients → 1 -23 160 -336

Testcase 2
Roots are very large (bases 3, 6, 7, 8, 12, 15, 16). After converting and expanding:
Coefficients →
1 -551626073038537993 -44494929400726500827110422439924177 1507808071887586020409274483918475186379622219 -15899633305913643940517685724614663425704394020145965 2972906771421478754400475911651588693652279133068350231610 -37148145806622331647621386816316845632395087204342819609381253 190613718831993610287528685750580270490404096183879901
