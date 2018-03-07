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
