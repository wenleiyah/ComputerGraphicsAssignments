# ComputerGraphicsAssignments
Assignments for Computer Graphics course of Politecnico di Milano 2025-2026

## Project structure

Each folder contains a self-contained Vulkan application that focuses on a specific topic covered during the course. The assignments are designed to be run independently.

- **A01 – 3D Transformations:** showcases a gallery of fifteen textured models and an axis helper that can be inspected under different model, view, and normal matrices while learning how descriptor sets and pipelines are assembled for the scene.
- **A02 – Projections:** demonstrates how switching among eight projection matrices (orthographic, axonometric, and perspective variants) affects a loaded scene, combining a procedurally created ground plane with assets described in JSON.
- **A03 – World View Projection:** loads a multi-part vehicle scene and allows toggling between third- and first-person camera rigs to study how view-projection updates change the rendering.
- **A05 – Third-person Game Logic:** implements a damped third-person character controller that reads six-axis input, updates the avatar transform, and positions a chase camera before composing the final view-projection matrix.
- **A07 – BRDF Shading:** compares Lambert and Blinn lighting models on a scene described through JSON by configuring multiple vertex layouts, pipelines, and descriptor sets for BRDF experimentation.
