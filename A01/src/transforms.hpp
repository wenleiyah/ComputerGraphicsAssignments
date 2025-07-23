void SetTransform(A01 *A) {
	/**************
	Using A->SetMatrix(i, M, focus) where:
	 i -> index of the matrix to set (0 .. 14)
	 M -> transform matrix to use
	 focus -> true if you want to add the focus to that piece (only one please)

	 solve the puzzle. Piece 0 is alread in place, and the correct transform to put in place piece 1, is
	 the identity matrix. Find the correct transformations to place the other 13 pieces (i = 2..14).
	 The suggestion is to work on the pieces one at a time, setting the focus to the one you are working on.
	 The piece with the focus, will be displayed in red. Moreover, its origin, and the orientation and size
	 of its axis will be shown. This is necessary because not all the pieces have their center in the origin,
	 but remember that the transformations, assumes that the center is in the origin. Some pieces (especially
	 the ones with a high index) will require a combination of transformations, since the transform is not
	 centered with the origin or the main axes. Follow the instructions in the comments to solve the puzzle.

	 WARNING!
	 Since it is a C program, you can use for loops and functions if you think they can be helpful in your solution.
	 However, please include all your code in this file, since it will be put in an automatic correction process
	 for the final evaluation. Please also be cautious when using standard libraries and symbols, since they
	 might not be available in all the development environments (especially, they might not be available
	 in the final evaluation environment, preventing your code from compiling).
	 This WARNING will be valid far ALL THE ASSIGNMENTs, but it will not be repeated in the following texts,
	 so please remember these advices carefully!

	***************/

    glm::mat4 M;

	// 1. This is the only one in place, and that should not be modified
	M = glm::mat4(1.0f); //define a unit matrix
	A->SetMatrix(0,  M, false);

	// 2. This is an example on how to highlight a piece and move it.
	// to put it in place, just replace the following line with an identity matrix,
	// that is: A->SetMatrix(0,  M, false);
	// M = glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(-0.3f, 0.0f, -1.6f)),
	// 				glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::mat4(1.0f);			// to put this piece in places, uncomment this line and delete the two above
	A->SetMatrix(1,  M, false);

	// FROM THIS POINT ON, you have to find the correct transform to solve the puzzle.

    // Lesson - 3. Translate 3 units along the y-axis and -2 along the z-axis.
	M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.0f, -2.0f));
    A->SetMatrix(2, M, false);

    // Lesson - 4. Rotate 30 degrees around the x-axis.
	M = glm::rotate(glm::mat4(1.0f),glm::radians(30.f), glm::vec3(1.0f, 0.0f, 0.0f));
	A->SetMatrix(3, M, false);

    // 5. Mirror over the xz-plane.
	M = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 1.0f));
    A->SetMatrix(4, M, false);

    // 6. Perform a shear along the y-axis, with hx = 0.4 (and hz = 0).
	M = glm::mat4(1.0f);
	M[1][0]=0.4f;
    A->SetMatrix(5, M, false);

    // 7. Scale by 1.5 along the z-axis and 0.75 along the y-axis.
	M = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.75f, 1.5f));
	A->SetMatrix(6, M, false);

    // 8. Perform a proportional scaling of a factor of 2.5.
	M = glm::scale(glm::mat4(1.0f), glm::vec3(2.5f, 2.5f, 2.5f));
    A->SetMatrix(7, M, false);

    //Lesson - 9. Scale 3x proportionally, centered at (-1,0,2).
	glm::mat4 T9 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 2.0f));
	glm::mat4 S9 = glm::scale(T9, glm::vec3(3.0f, 3.0f, 3.0f));
	// computation start from right, use inverse to moving back the rotation center to the origin, then doing the scale around origin, then move the puzzle back to the initial place
	M=S9*glm::inverse(T9);
	A->SetMatrix(8, M, false);

    // 10. Scale 1.5x along an axis oriented 45 degrees between the y and z-axis and passing through point (0,2,-1).
	glm::mat4 T10 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, -1.0f));
	glm::mat4 Ry10 = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Rz10 = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 R10 =  Ry10 * Rz10;
	glm::mat4 S10 = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.0f, 1.0f));
	M=T10 * R10 * S10 * glm::inverse(R10)*glm::inverse(T10);
    A->SetMatrix(9, M, false);

    // 11. Compose a rotation of 45 degrees around an axis aligned with the vector (-2,1,0), then a translation (2,0,-3).
	glm::vec3 v11= glm::normalize(glm::vec3(-2.0f, 1.0f, 0.0f));
	glm::mat4 R11 = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), v11);
	glm::mat4 T11 = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -3.0f));
	M= T11* R11;
    A->SetMatrix(10, M, false);

    // 12. Rotate -45 degrees around the z-axis, centered at (3,-1,0).
	glm::mat4 T12 = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, -1.0f, 0.0f));
	glm::mat4 R12 = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	M = T12 * R12  * glm::inverse(T12);
    A->SetMatrix(11, M, false);

    // 13. Perform a 90-degree rotation about an arbitrary axis passing through (0,0,-2), aligned using a 30-degree rotation around the z-axis and a 20-degree rotation around the y-axis.
	glm::mat4 Ry13 = glm::rotate(glm::mat4(1.0f),glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Rz13 = glm::rotate(glm::mat4(1.0f),glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 Rx13 = glm::rotate(glm::mat4(1.0f),glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 T13 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
	M = T13 * Rz13 * Ry13 * Rx13 * glm::inverse(Ry13) * glm::inverse(Rz13) * glm::inverse(T13);
    A->SetMatrix(12, M, false);

    // 14. Compose a non-proportional scaling that doubles the object along the y-axis, centered in (1,2,-1), with a translation (-2,0,3).
	glm::mat4 T14 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, -1.0f));
	glm::mat4 S14 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 1.0f));
	glm::mat4 T14_2 = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 3.0f));
	M = T14_2 * T14 * S14 * glm::inverse(T14);
    A->SetMatrix(13, M, false);

    // 15. Rotate 120 degrees around a custom axis passing through (2,-1,3) and aligned with the vector (1,2,1).
	glm::vec3 v15= glm::normalize(glm::vec3(1.0f, 2.0f, 1.0f));
	glm::mat4 R15 = glm::rotate(glm::mat4(1.0f), glm::radians(120.0f), v15);
	glm::mat4 T15 = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, -1.0f, 3.0f));
	M =  T15 * R15 * glm::inverse(T15);
    A->SetMatrix(14, M, false);
}
