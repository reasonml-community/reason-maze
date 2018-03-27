let maybe = (f, n) =>
  switch (n) {
  | None => None
  | Some(x) => Some(f(x))
  };

let shuffle = d => {
  let nd = Belt.List.map(d, c => (Random.bits(), c));
  let sond = List.sort(compare, nd);
  Belt.List.map(sond, snd);
};

module Float = {
  let (+) = (t, t') => t +. t';

  let (-) = (t, t') => t -. t';

  let (/) = (t, t') => t /. t';

  let ( * ) = (t, t') => t *. t';
};

module IntPairComparator =
  Belt.Id.MakeComparable({
    type t = (int, int);

    let cmp = ((x, y), (a, b)) =>
      switch (compare(x, a)) {
      | 0 => compare(y, b)
      | v => v
      };
  });

type intPairSet = Belt.Set.t((int, int), IntPairComparator.identity);

let intPairSet = Belt.Set.make(~id=(module IntPairComparator));
