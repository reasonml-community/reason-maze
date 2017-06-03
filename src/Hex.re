
let adjacent _ => [
  (-1, 0),
  ( 1, 0),
  (0, -1),
  (0,  1),
  (-1, 1),
  (1, -1),
];

type direction =
  | Xminus
  | Xplus
  | Yminus
  | Yplus
  | Zx
  | Zy;

let to_direction (dx, dy) => switch (dx, dy) {
  | (-1, 0) => Some Xminus
  | ( 1, 0) => Some Xplus
  | (0, -1) => Some Yminus
  | (0,  1) => Some Yplus
  | (-1, 1) => Some Zy
  | (1, -1) => Some Zx
};

let sq3 = sqrt 3.0;

let wall_in_direction direction => {
  open Utils.Float;
  let pts = switch direction {
    | Zx => (
        (1.0 / 2.0, 1.0 * sq3 / 2.0 - 1.0 / sq3),
        (1.0 / 2.0, -1.0 * sq3 / 2.0 + 1.0 / sq3)
      )
    | Zy => (
        (-1.0 / 2.0, 1.0 * sq3 / 2.0 - 1.0 / sq3),
        (-1.0 / 2.0, -1.0 * sq3 / 2.0 + 1.0 / sq3)
      )
    | Yminus => (
        (0.0, -1.0 / sq3),
        (1.0 / 2.0, -1.0 * sq3 / 2.0 + 1.0 / sq3)
      )
    | Yplus => (
        (0.0, 1.0 / sq3),
        (-1.0 / 2.0, 1.0 * sq3 / 2.0 - 1.0 / sq3)
      )
    | Xminus => (
        (0.0, -1.0 / sq3),
        (-1.0 / 2.0, -1.0 * sq3 / 2.0 + 1.0 / sq3)
      )
    | Xplus => (
        (0.0, 1.0 / sq3),
        (1.0 / 2.0, 1.0 * sq3 / 2.0 - 1.0 / sq3)
      )
  };
  Shared.Line pts;
};

