// mex operation:
// mex(S) refers to the smallest non-negative integer that does not belong to the set S; mex({0, 1, 3}) = 2, mex({1, 2, 4}) = 0.

// terminal state SG(S_0) = 0; for any non-terminal state S, SG(S) =  mex{SG(S') | S' is a successor states of S}.
// SG(S) != 0 ? win : lose;

// complex game composed of multiple independent subgames, its total SG value equals to the xor sum of the SG values of all the subgames.
