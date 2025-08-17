

void GameLogic(A05 *A, float Ar, glm::mat4 &ViewPrj, glm::mat4 &World) {
	// The procedure must implement the game logic  to move the character in third person.
	// Input:
	// <A05 *A> Pointer to the current assignment code. Required to read the input from the user
	// <float Ar> Aspect ratio of the current window (for the Projection Matrix)
	// Output:
	// <glm::mat4 &ViewPrj> the view-projection matrix of the camera
	// <glm::mat4 &World> the world matrix of the object
	// Parameters
	// Camera FOV-y, Near Plane and Far Plane
	const float FOVy = glm::radians(45.0f);
	const float nearPlane = 0.1f;
	const float farPlane = 100.f;
	
	// Player starting point
	const glm::vec3 StartingPosition = glm::vec3(-41.50, 0.0, -19.5);
	
	// Camera target height and distance
	const float camHeight = 0.25;
	const float camDist = 1.5;
	// Camera Pitch limits
	const float minPitch = glm::radians(-8.75f);
	const float maxPitch = glm::radians(60.0f);
	// Rotation and motion speed
	const float ROT_SPEED = glm::radians(120.0f);
	const float MOVE_SPEED = 2.0f;

	// Damping factor for the camera smoothing
	const float DAMP_LAMBDA = 10.0f;

	// Integration with the timers and the controllers
	// returns:
	// <float deltaT> the time passed since the last frame
	// <glm::vec3 m> the state of the motion axes of the controllers (-1 <= m.x, m.y, m.z <= 1)
	// <glm::vec3 r> the state of the rotation axes of the controllers (-1 <= r.x, r.y, r.z <= 1)
	// <bool fire> if the user has pressed a fire button (not required in this assginment)
	float deltaT;
	glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
	bool fire = false;
	A->getSixAxis(deltaT, m, r, fire);

	// Game Logic implementation
	// Current Player Position - statc variables make sure thattheri value remain unchanged in subsequent calls to the procedure
	static glm::vec3 Pos = StartingPosition;
    static float Pitch = glm::radians(0.0f);
    static float Yaw = glm::radians(0.0f);
    static float Roll = glm::radians(0.0f);

	Yaw -= ROT_SPEED * r.y * deltaT;
	Pitch -= ROT_SPEED * r.x * deltaT;
	Roll -= ROT_SPEED * r.z * deltaT;

	glm::vec3 ux = glm::vec3(glm::rotate(glm::mat4(1.0f), Yaw, glm::vec3(0,1,0)) * glm::vec4(1,0,0,1));
	glm::vec3 uz = glm::vec3(glm::rotate(glm::mat4(1.0f), Yaw, glm::vec3(0,1,0)) * glm::vec4(0,0,1,1));
    glm::vec3 uy = glm::vec3(0, 1, 0);

    // Update the player position
	Pos += MOVE_SPEED * ( m.x * ux + m.y * uy + m.z * uz ) * deltaT;

    World = glm::translate(glm::mat4(1.0f), Pos) *
			glm::rotate(glm::mat4(1.0f), Yaw, glm::vec3(0, 1, 0));

    // Clamp the pitch value
	Pitch = glm::clamp(Pitch, minPitch, maxPitch);
    glm::vec3 a = glm::vec3(World * glm::vec4(0,0,0,1)) + glm::vec3(0,0,camHeight);
	glm::vec3 camera(0.0f, camHeight + camDist * std::sin(Pitch), camDist * std::cos(Pitch));
    glm::vec3 c_new = glm::vec3(World * glm::vec4(camera, 1.0f));

    // Smooth the camera position
	float ef = std::exp(-DAMP_LAMBDA * deltaT);
	static glm::vec3 CamPosSmoothed = StartingPosition + glm::vec3(0, camHeight, camDist);
	CamPosSmoothed = ef * CamPosSmoothed + (1.0f - ef) * c_new;

    // Set the ViewPrj matrix
	const float frameOffsetY = 0.35f;
	glm::vec3 a_framed = a + frameOffsetY * glm::vec3(0,1,0);

	glm::mat4 View = glm::lookAt(CamPosSmoothed, a_framed, glm::vec3(0,1,0));
	glm::mat4 Proj = glm::perspective(FOVy, Ar, nearPlane, farPlane);
	Proj[1][1] *= -1.0f;

    ViewPrj = Proj * View;
}