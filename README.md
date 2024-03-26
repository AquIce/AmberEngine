# AmberEngine

**AmberEngine** is my try at the creation of a basic 3D engine displaying only in isometric projection.

## Engine

### TODO List (2024.03.25 - 2024.03.26)

- [x] Define cube with points rather than lines
  - [x] Change Cube implementation to use points
  - [x] Change draw_line implementation calculate lines from points
- [x] 3D coordinate system (x, y, z) -> screen position (x, y)
  - [x] Create 3D coordinate struct with x, y, z
  - [x] Add origin property to SDL3Config
  - [x] Add converter using SDL3Config differents sizes
- [x] Visible render
  - [x] Render only visible dots
  - [x] Render only visible lines
