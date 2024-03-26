# PostSurvivor

## Engine

### TODO List (2024.03.25 - 2024.03.25)

- [x] Define cube with points rather than lines
  - [x] Change Cube implementation to use points
  - [ ] Change draw_line implementation calculate lines from points (needs visible renderer to avoid drawing multiple lines)
- [x] 3D coordinate system (x, y, z) -> screen position (x, y)
  - [x] Create 3D coordinate struct with x, y, z
  - [x] Add origin property to SDL3Config
  - [x] Add converter using SDL3Config differents sizes
- [ ] Visible render
  - [ ] Render only visible dots
  - [ ] Render only visible lines
  - [ ] Render only visible faces