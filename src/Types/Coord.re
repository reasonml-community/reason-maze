
module type T = {
  type t;
  let offset: t => t => t;
}
