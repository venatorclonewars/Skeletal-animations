#include "game.h"
#include <stdio.h>
#include <string>
#include "camera.h"
#include "texture.h"
#include "mesh.h"
#include "meshSkeleton.h"
#include "lighting_technique.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

GLuint VAO = -1;
GLuint VBO = -1;
GLuint IBO = -1;

Texture* pTexture = NULL;
Mesh* pMesh = NULL;
MeshSkeleton* pMeshSkeleton = NULL;
LightingTechnique* pLightingTech = NULL;
BaseLight baseLight;
DirectionalLight dirLight;

Camera camera;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

Game::Game()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    // First init this window, later fullscreen
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    int x = 200;
    int y = 100;
    glutInitWindowPosition(x, y);
    int win = glutCreateWindow("BattlefrontRemake");
    printf("window id: %d\n", win);

    glutFullScreen();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) 
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        exit(1);
    }

    pMesh = new Mesh();
    pMeshSkeleton = new MeshSkeleton();

    pMeshSkeleton->importMesh("Models/Doom/boblampclean.md5mesh");

    //Models/Chess/chess_set_1k.fbx
    if (!pMesh->loadMesh("Models/Vase/antique_ceramic_vase_01_1k.fbx"))
        exit(1);


    
    pLightingTech = new LightingTechnique();
    if (!pLightingTech->init())
        exit(1);
    

    pLightingTech->enable();

    pLightingTech->setTextureUnit(COLOR_TEXTURE_UNIT_INDEX_0);
    pLightingTech->setSpecularExpTextureUnit(SPECULAR_EXPONENT_UNIT_INDEX_0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    dirLight.ambientIntensity = 0.1f;
    dirLight.diffuseIntensity = 1.0f;
    dirLight.worldDirection = Vector3f(10.0f, 0.0f, 50.0f);

    
}

void Game::run()
{
    GLclampf red = 0.0f, green = 0.0f, blue = 0.0f, alpha = 0.0f;
    glClearColor(red, green, blue, alpha);

    glutCallbacks();

    glutMainLoop();
}

void Game::renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float FOV = 45.0f;

    float aspectRatio = (float)glutGet(GLUT_SCREEN_WIDTH) / (float)glutGet(GLUT_SCREEN_HEIGHT);
    float nearZ = 1.0f;
    float farZ = 1000.0f;

    Matrix4f projection;
    projection.setProjection(FOV, aspectRatio, nearZ, farZ);

    Matrix4f temp, view, world;

    temp.setIdentity();
    temp.setRotationY(camera.rotY);
    view *= temp;

    temp.setIdentity();
    temp.setRotationX(camera.rotX);
    view *= temp;

    

    Matrix4f camTranslation = camera.getMatrix();
    view.setTranslation(camTranslation.getTranslation());
    camera.cameraTransform = view;

    view.inverse();
  
    world = pMesh->getWorldTransform();
    world.setScale(Vector3f(5.0f, 5.0f, 5.0f));

    Matrix4f WVP = projection * view * world;
    pLightingTech->setWVP(WVP);
    pLightingTech->setDirectionalLight(dirLight);
    pLightingTech->setMaterial(pMesh->getMaterial());
    dirLight.calcLocalDirection(world);


    // Reflection
    Matrix4f camToLocalTrans;
    camToLocalTrans.setTranslation(camera.transformPos.negate());

    Matrix4f camToLocalRot(view);
    camToLocalRot = camToLocalRot.transpose();

    Matrix4f camToLocalTransform = camToLocalRot * camToLocalTrans;

    Vector4f cameraWorldPos = Vector4f(camera.transformPos.x, camera.transformPos.y, camera.transformPos.z, 1.0f);
    //Vector4f camLocalPos = camToLocalTrans * cameraWorldPos;
    Vector4f camLocalPos = camToLocalTrans * Vector4f(camera.transformPos.x, camera.transformPos.y, camera.transformPos.z, 0.0f);

    Vector3f camLocalPos3f = Vector3f(camLocalPos.x, camLocalPos.y, camLocalPos.z);

    pLightingTech->setCameraLocalPos(camLocalPos3f);

    pMesh->render();
    
    glutSwapBuffers();

}

void Game::displayNewFrame(int deltaTime)
{
    glutPostRedisplay();
    // call timerFunction again after ~16 ms (for ~60 FPS)
    glutTimerFunc(16, displayNewFrame, 0);
}

void Game::keyboardListener(unsigned char key, int mouse_x, int mouse_y)
{
    camera.onKeyboard(key);
}

void Game::specialKeyboardListener(int key, int mouse_x, int mouse_y)
{
    camera.onKeyboard(key);
}

void Game::mouseListener(int x, int y)
{
    camera.onMouse(x, y);
}

void Game::glutCallbacks()
{
    displayNewFrame(16);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyboardListener);
    glutPassiveMotionFunc(mouseListener);
    glutDisplayFunc(renderScene);
}
