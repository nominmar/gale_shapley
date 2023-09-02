#### Introduction
Gale-Shapley algorithm for stable matching in C++ from [College Admissions and the Stability of Marriage](https://www.tandfonline.com/doi/abs/10.1080/00029890.1962.11989827?journalCode=uamm20) paper by Gale, D.; Shapley, L. S. (1962)

With two equally sized sets of elements given an ordering of preferences for each element, create a stable matching, where there is no pair which both prefer each other to their current partner under the matching.

#### How to
(1) Start with 2 equal sized vectors and 2 vectors of preferences <br>
(2) Create a vector of booleans to capture proposing side's (gale) matched status. And vector of strings to capture receiving side's (shapley) current matches. Use shapley match vector to capture final outcome  <br>
(3) Gale always proposes to the first preference on it's preference list <br>
(4) When receiving a proposal, shapley evaluates it against it's preference list and accept/rejects <br>
(5a) If proposal is accepted, gale's match is set to true <br>
(5b) If a proposal if rejected, gale's match is set to false. The current (highest) preference is removed from the preference list <br>
(5c) If a successful proposal breaks existing match, set the existing match's gale match to false <br>
(6) Run the algorithm until all gales have a match (=until gale match vector has no false's) <br>
