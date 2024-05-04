#include "pch.h"

#include "cControlGameEngine.h"
#include "PlayerAttributes.h"

extern cControlGameEngine gameEngine;

const float POSITION_OFFSET = 0.0f;

extern sPlayerAttributes playerAttributes;

cMesh* controlMeshModel;

void resetCamAttributes()
{
    if (!gameEngine.mouseMoved)
        gameEngine.mouseMoved = true;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    float ROTATION_DEGREES = 5.0f;

    const float CAMERA_SPEED = 300.0f;

    const float MODEL_MOVE_SPEED = 1.0f;

    float CAMERA_MOVEMENT = CAMERA_SPEED * gameEngine.deltaTime;

    glm::vec3 CAMERA_TARGET = gameEngine.GetCurrentCameraTarget();
    glm::vec3 CAMERA_UP = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 CAMERA_POSITION = gameEngine.GetCurrentCameraPosition();


    if (mods == 0)
    {
        //------------------------------Camera Showcases------------------------------------------------

        if (key == GLFW_KEY_1 && action)
        {
            CAMERA_POSITION = glm::vec3(0.0f + POSITION_OFFSET, 50.0f + POSITION_OFFSET, 300.0f + POSITION_OFFSET);
            gameEngine.MoveCameraTarget(0.0f, 0.0f, -1.0f);
            gameEngine.yaw = -90.0f;
            gameEngine.pitch = 0.f;
            resetCamAttributes();
        }

        if (key == GLFW_KEY_2 && action)
        {
            CAMERA_POSITION = glm::vec3(-290.0f + POSITION_OFFSET, 70.0f + POSITION_OFFSET, 0.f + POSITION_OFFSET);
            gameEngine.MoveCameraTarget(1.f, -0.06f, 0.03f);
            gameEngine.yaw = -358.241f;
            gameEngine.pitch = -3.65f;
            resetCamAttributes();
        }

        if (key == GLFW_KEY_3 && action)
        {
            CAMERA_POSITION = glm::vec3(-4.25f + POSITION_OFFSET, 55.f + POSITION_OFFSET, -280.f + POSITION_OFFSET);
            gameEngine.MoveCameraTarget(-0.0115f, 0.009f, 1.0f);
            gameEngine.yaw = -269.345f;
            gameEngine.pitch = 0.5f;
            resetCamAttributes();
        }

        if (key == GLFW_KEY_4 && action)
        {
            CAMERA_POSITION = glm::vec3(270.f + POSITION_OFFSET, 53.f + POSITION_OFFSET, 6.f + POSITION_OFFSET);
            gameEngine.MoveCameraTarget(-1.f, -0.016f, -0.035f);
            gameEngine.yaw = -177.998f;
            gameEngine.pitch = -0.9f;
            resetCamAttributes();
        }

        if (key == GLFW_KEY_5 && action)
        {
            CAMERA_POSITION = glm::vec3(2.5f + POSITION_OFFSET, 450.f + POSITION_OFFSET, 100.f + POSITION_OFFSET);
            gameEngine.MoveCameraTarget(-0.0012f, -0.98f, -0.22f);
            gameEngine.yaw = -90.3f;
            gameEngine.pitch = -77.55f;
            resetCamAttributes();
        }

        if (key == GLFW_KEY_SPACE && action)
        {
            if (gameEngine.enableMouseMovement)
                gameEngine.enableMouseMovement = false;
            else
                gameEngine.enableMouseMovement = true;

            resetCamAttributes();
        }

        //------------------------------Move Camera--------------------------------------------------------

        if (key == GLFW_KEY_W && action)
        {
            CAMERA_POSITION += CAMERA_MOVEMENT * CAMERA_TARGET;
        }
        if (key == GLFW_KEY_A && action)
        {
            CAMERA_POSITION -= glm::normalize(glm::cross(CAMERA_TARGET, CAMERA_UP)) * CAMERA_MOVEMENT;
        }
        if (key == GLFW_KEY_S && action)
        {
            CAMERA_POSITION -= CAMERA_MOVEMENT * CAMERA_TARGET;
        }
        if (key == GLFW_KEY_D && action)
        {
            CAMERA_POSITION += glm::normalize(glm::cross(CAMERA_TARGET, CAMERA_UP)) * CAMERA_MOVEMENT;
        }
        if (key == GLFW_KEY_Q && action)
        {
            CAMERA_POSITION += CAMERA_MOVEMENT * CAMERA_UP;
        }
        if (key == GLFW_KEY_E && action)
        {
            CAMERA_POSITION -= CAMERA_MOVEMENT * CAMERA_UP;
        }

        gameEngine.MoveCameraPosition(CAMERA_POSITION.x, CAMERA_POSITION.y, CAMERA_POSITION.z);
    }

    return;
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if (gameEngine.enableMouseMovement)
    {
        glm::vec3 CAMERA_UP = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 CAMERA_POSITION = gameEngine.GetCurrentCameraPosition();

        int screenWidth, screenHeight;
        glfwGetWindowSize(window, &screenWidth, &screenHeight);

        float mouseSensitivity = 0.05f;

        float xOffset = 0.0f;
        float yOffset = 0.0f;

        if (xPos >= screenWidth - 1 || xPos <= 0) // Rotate Cam when mouse moves to the edge of the screen(left or right)
        {
            xOffset = 0.0f;

            if (xPos <= 0)
                xOffset = -10.0f;
            else if (xPos >= screenWidth - 1)
                xOffset = 10.0f;

            gameEngine.yaw += mouseSensitivity * xOffset;
        }

        if (yPos >= screenHeight - 1 || yPos <= 20) // Rotate Cam when mouse moves to the edge of the screen(up or down)
        {
            yOffset = 0.0f;

            if (yPos <= 20)
                yOffset = 10.0f;
            else if (yPos >= screenHeight - 1)
                yOffset = -10.0f;

            gameEngine.pitch += mouseSensitivity * yOffset;
        }

        if (gameEngine.mouseMoved)
        {
            gameEngine.previousX = xPos;
            gameEngine.previousY = yPos;
            gameEngine.mouseMoved = false;
        }

        xOffset = xPos - gameEngine.previousX;
        yOffset = gameEngine.previousY - yPos; //Reversed Y

        xOffset *= mouseSensitivity;
        yOffset *= mouseSensitivity;

        gameEngine.yaw += xOffset;
        gameEngine.pitch += yOffset;

        if (gameEngine.pitch > 90.0f)
            gameEngine.pitch = 90.0f;

        if (gameEngine.pitch < -90.0f)
            gameEngine.pitch = -90.0f;

        glm::vec3 front;

        front.x = cos(glm::radians(gameEngine.yaw)) * cos(glm::radians(gameEngine.pitch));
        front.y = sin(glm::radians(gameEngine.pitch));
        front.z = sin(glm::radians(gameEngine.yaw)) * cos(glm::radians(gameEngine.pitch));

        glm::vec3 cameraFront = glm::normalize(front);

        gameEngine.MoveCameraTarget(cameraFront.x, cameraFront.y, cameraFront.z);

        gameEngine.previousX = xPos;
        gameEngine.previousY = yPos;
    }
}