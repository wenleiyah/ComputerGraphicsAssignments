/**************
	Compute the world view and projection matrices, as described below

	WARNING!
	Since it is a C program, you can use for loops and functions if you think they can be helpful in your solution.
	However, please include all your code in this file, since it will be put in an automatic correction process
	for the final evaluation. Please also be cautious when using standard libraries and symbols, since they
	might not be available in all the development environments (especially, they might not be available
	in the final evaluation environment, preventing your code from compiling).
	This WARNING will be valid far ALL THE ASSIGNMENTs, but it will not be repeated in the following texts,
	so please remember these advices carefully!
 
***************/
glm::mat4 MakeViewProjectionLookInDirection(glm::vec3 Pos, float Yaw, float Pitch, float Roll, float FOVy, float Ar, float nearPlane, float farPlane) {
	// Make a View-Projection matrix, where the view matrix uses the look-in-direction model,
	// and the projection matrix supports perspective. Parameters are the following:
	// Projection:
	//	- Perspective with:
	//	- Fov-y defined in formal parameter >FOVy<
	//  - Aspect ratio defined in formal parameter >Ar<
	//  - Near Plane distance defined in formal parameter >nearPlane<
	//  - Far Plane distance defined in formal parameter >farPlane<
	// View:
	//	- Use the Look-In-Direction model with:
	//	- Camera Positon defined in formal parameter >Pos<
	//	- Looking direction defined in formal parameter >Yaw<
	//	- Looking elevation defined in formal parameter >Pitch<
	//	- Looking rool defined in formal parameter >Roll<

	// SOLUTIONS:
    // Declare the projection and view matrices

	// Projection matrix
    glm::mat4 Proj = glm::perspective(FOVy, Ar, nearPlane, farPlane);
	//flip the y axis
    Proj[1][1] *= -1;

	// View matrix
    // Translation matrix to move the camera to the position specified by Pos
	glm::mat4 Trans = glm::translate(glm::mat4(1.0f), Pos);
	// Rotation matrices for roll, pitch and yaw, following the Z-X-Y convention
	glm::mat4 Rx = glm::rotate(glm::mat4(1), Pitch, glm::vec3(1, 0, 0));
	glm::mat4 Ry = glm::rotate(glm::mat4(1), Yaw, glm::vec3(0, 1, 0));
	glm::mat4 Rz = glm::rotate(glm::mat4(1), Roll, glm::vec3(0, 0, 1));

	//Rotation order always from right to left, so we first apply the roll, then the pitch and finally the yaw
	glm::mat4 View = glm::inverse(Trans * Ry * Rx * Rz);
	glm::mat4 M = Proj * View;

	return M;
}

glm::mat4 MakeViewProjectionLookAt(glm::vec3 Pos, glm::vec3 Target, glm::vec3 Up, float Roll, float FOVy, float Ar, float nearPlane, float farPlane) {
	// Make a View-Projection matrix, where the view matrix uses the look-at model,
	// and the projection matrix supports perspective. Parameters are the following:
	// Projection:
	//	- Perspective with:
	//	- Fov-y defined in formal parameter >FOVy<
	//  - Aspect ratio defined in formal parameter >Ar<
	//  - Near Plane distance defined in formal parameter >nearPlane<
	//  - Far Plane distance defined in formal parameter >farPlane<
	// View:
	//	- Use the Look-At model with:
	//	- Camera Positon defined in formal parameter >Pos<
	//	- Camera Target defined in formal parameter >Target<
	//	- Up vector defined in formal parameter >Up<
	//	- Looking rool defined in formal parameter >Roll<

	// SOLUTIONS:

	// Projection matrix
	glm::mat4 Proj = glm::perspective(FOVy, Ar, nearPlane, farPlane);
	//flip the y axis
	Proj[1][1] *= -1;

	// View matrix
	glm::mat4 Rol = glm::rotate(glm::mat4(1), -Roll, glm::vec3(0, 0, 1));
	glm::mat4 lookAt = glm::lookAt(Pos, Target, Up);
	glm::mat4 View = Rol * lookAt;

	glm::mat4 M = Proj * View;

	return M;
}

glm::mat4 MakeWorld(glm::vec3 Pos, float Yaw, float Pitch, float Roll) {
	// Make a World matrix, where rotation is specified using Euler’s angles,
	// with the zxy convention (z for roll, x for pitch and y for yaw).
	// Scaling is considered always equal to 1, and thus it is not passed to the procedure.
	// Parameters are the following:
	//	- Object Positon defined in formal parameter >Pos<
	//	- Euler angle rotation yaw defined in formal parameter >Yaw<
	//	- Euler angle rotation pitch defined in formal parameter >Pitch<
	//	- Euler angle rotation roll defined in formal parameter >Roll<
	//  - Scaling constant and equal to 1 (and not passed to the procedure)


	// SOLUTIONS:
	// Translation matrix to move the object to the position specified by Pos
	glm::mat4 Trans = glm::translate(glm::mat4(1.0f), Pos);

	// Rotation matrices for roll, pitch and yaw, following the Z-X-Y convention
	glm::mat4 Rx = glm::rotate(glm::mat4(1), Pitch, glm::vec3(1, 0, 0));
	glm::mat4 Ry = glm::rotate(glm::mat4(1), Yaw, glm::vec3(0, 1, 0));
	glm::mat4 Rz = glm::rotate(glm::mat4(1), Roll, glm::vec3(0, 0, 1));

	glm::mat4 M = Trans * Ry * Rx * Rz;
	return M;
}
