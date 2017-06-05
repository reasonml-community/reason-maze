
module type T = {
  type t;
  let offset: t => t => t;
  let compare: t => t => int;
}
