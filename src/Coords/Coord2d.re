type t = (int, int);

let offset = ((x, y), (a, b)) => (x + a, y + b);

let compare = (a: t, b: t) : int => compare(a, b);
