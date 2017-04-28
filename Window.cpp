#include "window.h"
#include "OBJObject.h"
#include "Skybox.hpp"

const char* window_title = "GLFW Starter Project";
GLuint shaderProgram;
GLuint skyboxShader;

Skybox * cubemap;
Geode * geoCylinder;
Geode * geo_child;
Geode * geoPod;

MatrixTransform * L2setA ;

MatrixTransform * m_root;
MatrixTransform * m_cyl2;
MatrixTransform * m_pod ;
MatrixTransform *  m_cyl1;
MatrixTransform * level1 ;
MatrixTransform * level2 ;
MatrixTransform * level3 ;
MatrixTransform * set1;
MatrixTransform * set3;
MatrixTransform * L1arm_1;
MatrixTransform * subSet1;
MatrixTransform * L1A1F1;
MatrixTransform * L1A1F2;
MatrixTransform * L1A1F3;
MatrixTransform * L1arm_2;
MatrixTransform * subSet2;
MatrixTransform * L1arm_3;
MatrixTransform * subSet3;
MatrixTransform * L2arm_1;
MatrixTransform * L2arm_2;
MatrixTransform * L2arm_3;
MatrixTransform * L1pod_1;
MatrixTransform * L1pod_2;
MatrixTransform * L1pod_3;
MatrixTransform * L1pod_4;
MatrixTransform * L1pod_5;
MatrixTransform * L1pod_6;
MatrixTransform * L1pod_7;
MatrixTransform * L1pod_8;

MatrixTransform * L1A1;
MatrixTransform * L1A2;
MatrixTransform * L1A3;

MatrixTransform * L1A2F1;
MatrixTransform* L1A2F2;
MatrixTransform * L1A2F3;
MatrixTransform * L1A3F1;
MatrixTransform * L1A3F2;
MatrixTransform * L1A3F3;

MatrixTransform* trialsubset1;

MatrixTransform * L1A1F1p1;
MatrixTransform * L1A1F1p2;
MatrixTransform * L1A1F1p3;
MatrixTransform * L1A2F1p1;
MatrixTransform * L1A2F1p2;
MatrixTransform * L1A3F1p1;
MatrixTransform * L1A3F1p2;
MatrixTransform * L1A3F3p3;
MatrixTransform * L3A3F9pod_9;

MatrixTransform*  L3arm_1;
MatrixTransform*  L3arm_2;
MatrixTransform*  L3arm_3;

MatrixTransform *  L2fingerset1;
MatrixTransform *   L2fingerset2;
MatrixTransform *   L2fingerset3;
MatrixTransform*   L3subSet1;
MatrixTransform*   L3subSet2;
MatrixTransform*   L3subSet3;
MatrixTransform *  bearO ;
vector<Geode * > pods;

/**** Level 2 *******/
Geode * beargeo;
/*****************/
//center
MatrixTransform * c1;
MatrixTransform * c2;
MatrixTransform * c3 ;

glm::mat4 result;

glm::mat4 product;
bool obj_rot = false;
float ylev = 0.0f;
float offset = 0.15f;
float eOffset = 0.15f;
float rot_angle = 0.0f;
float rot_offset = 0.01f;
float extend = 0.0f;
//new
bool firstMouse =true;
bool bearOn  =false;
bool splitscreen = false;
bool lightsOn = false;

double Window::cur_x;
double Window::cur_y;
double Window::prev_x;
double Window::prev_y;
double Window::scrollX;
double Window::scrollY;

GLfloat yaw   = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch =   0.0f;

// Default camera parameters
glm::vec3 cam_pos(0.0f, 0.0f, 5.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, -1.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;
glm::mat4 Window::bearV;
glm::mat4 Window::bearP; 

void Window::initialize_objects()
{
    // Load the shader program. Similar to the .obj objects, different platforms expect a different directory for files
#ifdef _WIN32 // Windows (both 32 and 64 bit versions)
    skyboxShader = LoadShaders("../skyboxShader.vert", "../skyboxShader.frag");
#else // Not windows
    skyboxShader = LoadShaders("skyboxShader.vert", "skyboxShader.frag");
#endif
    
    //create the skybox
    std::vector<const GLchar*> faces;
    faces.push_back("/Users/Cocona2121/Desktop/CSE 167_1/Assignment_3/assignment_3/PPM_Files/Skybox_Water222_right.PPM");
    faces.push_back("/Users/Cocona2121/Desktop/CSE 167_1/Assignment_3/assignment_3/PPM_Files/Skybox_Water222_left.PPM");
    faces.push_back("/Users/Cocona2121/Desktop/CSE 167_1/Assignment_3/assignment_3/PPM_Files/Skybox_Water222_top.PPM");
    faces.push_back("/Users/Cocona2121/Desktop/CSE 167_1/Assignment_3/assignment_3/PPM_Files/Skybox_Water222_base.PPM");
    faces.push_back("/Users/Cocona2121/Desktop/CSE 167_1/Assignment_3/assignment_3/PPM_Files/Skybox_Water222_front.PPM");
    faces.push_back("/Users/Cocona2121/Desktop/CSE 167_1/Assignment_3/assignment_3/PPM_Files/Skybox_Water222_back.PPM");
    
    cubemap = new Skybox(faces);
   
    // Load the shader program. Similar to the .obj objects, different platforms expect a different directory for files
#ifdef _WIN32 // Windows (both 32 and 64 bit versions)
    shaderProgram = LoadShaders("../shader.vert", "../shader.frag");
#else // Not windows
    shaderProgram = LoadShaders("shader.vert", "shader.frag");
#endif
    
    //making the wedding cake
    OBJObject * cylinder = new OBJObject("/Users/Cocona2121/Desktop/CSE 167_1/Assignment_3/assignment_3/cylinder.obj");
    OBJObject * pod = new OBJObject ("/Users/Cocona2121/Desktop/CSE 167_1/Assignment_3/assignment_3/pod.obj");
    OBJObject * bear = new OBJObject("/Users/Cocona2121/Desktop/CSE 167_1/Assignment_3/assignment_3/bear.obj");
    
    geoCylinder = new Geode(cylinder, shaderProgram);
    beargeo = new Geode (bear , shaderProgram);
    Geode * mainCGeo = new Geode(cylinder, shaderProgram);
    
    Geode * geoCylinder2 = new Geode(cylinder, shaderProgram);
    Geode * geoCylinder3 = new Geode(cylinder, shaderProgram);
    Geode * geoArm1 = new Geode(cylinder, shaderProgram);
    Geode * geoArm1F = new Geode(cylinder, shaderProgram);
    Geode * geoArm2 = new Geode(cylinder, shaderProgram);
     Geode * geoArm2F = new Geode(cylinder, shaderProgram);
    Geode * geoArm3 = new Geode(cylinder, shaderProgram);
     Geode * geoArm3F = new Geode(cylinder, shaderProgram);
    
    Geode * geoSubArm1 = new Geode(cylinder, shaderProgram);
    Geode * geoSubArm2 = new Geode(cylinder, shaderProgram);
    Geode * geoSubArm3 = new Geode(cylinder, shaderProgram);
    Geode * geoSubArm4 = new Geode(cylinder, shaderProgram);
    Geode * geoSubArm5 = new Geode(cylinder, shaderProgram);
    Geode * geoSubArm6 = new Geode(cylinder, shaderProgram);
    Geode * geoSubArm7 = new Geode(cylinder, shaderProgram);
    Geode * geoSubArm8 = new Geode(cylinder, shaderProgram);
    Geode * geoSubArm9 = new Geode(cylinder, shaderProgram);
    
   Geode * geoPodL1A1 = new Geode(pod, shaderProgram);
    Geode * geoPodL1A2 = new Geode(pod, shaderProgram);
    Geode * geoPodL1A3 = new Geode(pod , shaderProgram);
    Geode* geosub2PodL1A1  = new Geode(pod, shaderProgram);
    Geode * geosub2PodL1A2  = new Geode(pod, shaderProgram);
    Geode * geosub2PodL1A3  = new Geode(pod, shaderProgram);
  Geode *  geoL1A3F1p1 = new Geode(pod, shaderProgram);
     Geode * geoL1A3F2p2 = new Geode(pod, shaderProgram);
    Geode * geoL1A3F3p3 = new Geode(pod, shaderProgram);
    
  
    pods.push_back(geoPodL1A1);
    pods.push_back(geoPodL1A2);
    pods.push_back(geoPodL1A3);
    pods.push_back(geosub2PodL1A1);
    pods.push_back(geosub2PodL1A2);
    pods.push_back(geosub2PodL1A3);
    pods.push_back(geoL1A3F1p1);
    pods.push_back(geoL1A3F2p2);
    pods.push_back(geoL1A3F3p3);
    
    /**************LEVEL 2********************/
    Geode * L2geoArm1 = new Geode(cylinder, shaderProgram);
    Geode * L2geoArm2 = new Geode(cylinder, shaderProgram);
    Geode * L2geoArm3 = new Geode(cylinder, shaderProgram);
    
    Geode * L2geoSubArm1 = new Geode(cylinder, shaderProgram);
    Geode * L2geoSubArm2 = new Geode(cylinder, shaderProgram);
    Geode * L2geoSubArm3 = new Geode(cylinder, shaderProgram);
    Geode * L2geoSubArm4 = new Geode(cylinder, shaderProgram);
    Geode * L2geoSubArm5 = new Geode(cylinder, shaderProgram);
    Geode * L2geoSubArm6 = new Geode(cylinder, shaderProgram);
    Geode * L2geoSubArm7 = new Geode(cylinder, shaderProgram);
    Geode * L2geoSubArm8 = new Geode(cylinder, shaderProgram);
    Geode * L2geoSubArm9 = new Geode(cylinder, shaderProgram);
    
    Geode * L2geoPodL1A1 = new Geode(pod, shaderProgram);
    Geode * L2geoPodL1A2 = new Geode(pod, shaderProgram);
    Geode * L2geoPodL1A3 = new Geode(pod , shaderProgram);
    Geode* L2geosub2PodL1A1  = new Geode(pod, shaderProgram);
    Geode * L2geosub2PodL1A2  = new Geode(pod, shaderProgram);
    Geode * L2geosub2PodL1A3  = new Geode(pod, shaderProgram);
    Geode * L2geoL1A3F1p1 = new Geode(pod, shaderProgram);
    Geode * L2geoL1A3F2p2 = new Geode(pod, shaderProgram);
    Geode * L2geoL1A3F3p3 = new Geode(pod, shaderProgram);
    
    pods.push_back(L2geoPodL1A1);
    pods.push_back(L2geoPodL1A2);
    pods.push_back(L2geoPodL1A3);
    pods.push_back(L2geosub2PodL1A1);
    pods.push_back(L2geosub2PodL1A2);
    pods.push_back(L2geosub2PodL1A3);
    pods.push_back(L2geoL1A3F1p1);
    pods.push_back(L2geoL1A3F2p2);
    pods.push_back(L2geoL1A3F3p3);
    
    Geode * L3geoArm1 = new Geode(cylinder, shaderProgram);
    Geode * L3geoArm2 = new Geode(cylinder, shaderProgram);
    Geode * L3geoArm3 = new Geode(cylinder, shaderProgram);
    
    Geode * L3geoSubArm1 = new Geode(cylinder, shaderProgram);
    Geode * L3geoSubArm2 = new Geode(cylinder, shaderProgram);
    Geode * L3geoSubArm3 = new Geode(cylinder, shaderProgram);
    Geode * L3geoSubArm4 = new Geode(cylinder, shaderProgram);
    Geode * L3geoSubArm5 = new Geode(cylinder, shaderProgram);
    Geode * L3geoSubArm6 = new Geode(cylinder, shaderProgram);
    Geode * L3geoSubArm7 = new Geode(cylinder, shaderProgram);
    Geode * L3geoSubArm8 = new Geode(cylinder, shaderProgram);
    Geode * L3geoSubArm9 = new Geode(cylinder, shaderProgram);
    
    Geode * L2geoArm1_fake = new Geode(cylinder , shaderProgram);
    Geode * L2geoArm2_fake = new Geode(cylinder , shaderProgram);
    Geode * L2geoArm3_fake = new Geode (cylinder , shaderProgram);
    
    Geode * L3geoArm1_fake = new Geode (cylinder, shaderProgram);
    Geode * L3geoArm2_fake = new Geode(cylinder, shaderProgram);
    Geode * L3geoArm3_fake = new Geode (cylinder, shaderProgram);
    
    Geode * L3geoPodL1A1 = new Geode(pod, shaderProgram);
    Geode * L3geoPodL1A2 = new Geode(pod, shaderProgram);
    Geode * L3geoPodL1A3 = new Geode(pod , shaderProgram);
    Geode* L3geosub2PodL1A1  = new Geode(pod, shaderProgram);
    Geode * L3geosub2PodL1A2  = new Geode(pod, shaderProgram);
    Geode * L3geosub2PodL1A3  = new Geode(pod, shaderProgram);
    Geode * L3geoL1A3F1p1 = new Geode(pod, shaderProgram);
    Geode * L3geoL1A3F2p2 = new Geode(pod, shaderProgram);
    Geode * L3geoL1A3F3p3 = new Geode(pod, shaderProgram);
    
    pods.push_back(L3geoPodL1A1);
    pods.push_back(L3geoPodL1A2);
    pods.push_back(L3geoPodL1A3);
    pods.push_back(L3geosub2PodL1A1);
    pods.push_back(L3geosub2PodL1A2);
    pods.push_back(L3geosub2PodL1A3);
    pods.push_back(L3geoL1A3F1p1);
    pods.push_back(L3geoL1A3F2p2);
    pods.push_back(L3geoL1A3F3p3);
    /***************************************/
    
    //making the identity roots for animations
    //root
    m_root = new MatrixTransform(glm::mat4(1.0f));
    
    /**************** CYLINDERS ************/
    level1 = new MatrixTransform(glm::mat4(1.0f));
    m_root -> addChild(level1);
    
    //level 2 root
    level2 = new MatrixTransform(glm::mat4(1.0f));
    m_root -> addChild(level2);
    
    //level 3 root
    level3 = new MatrixTransform(glm::mat4(1.0f));
    m_root -> addChild(level3);
    /***********************************/
    /********* LEVEL 1 -- ARM SET 1 **********/
    set1 = new MatrixTransform (glm::mat4(1.0f));
    level1->addChild(set1);
    /*****************************************/
    
    /************ LEVEL 1- ARMS *************/
    //level 1--arm root node
    L1arm_1 = new MatrixTransform(glm::mat4(1.0f));
    set1 ->addChild(L1arm_1);
    L1arm_2 = new MatrixTransform(glm::mat4(1.0f));
    set1 ->addChild(L1arm_2);
    L1arm_3 = new MatrixTransform(glm::mat4(1.0f));
    set1 ->addChild(L1arm_3);
    /*******************************************/
    
   /************** LEVEL 1 -- FINGER SET : finger sets rotate*********/
    subSet1 = new MatrixTransform(glm::mat4(1.0f));
    //trial
    L1arm_1 -> addChild(subSet1);
    subSet2 = new MatrixTransform(glm::mat4(1.0f));
    L1arm_2 -> addChild(subSet2);
    subSet3 = new MatrixTransform(glm::mat4(1.0f));
    L1arm_3 -> addChild(subSet3);
    /************************************************/
    
    /******** LEVEL 1 -- ARM 123 ---- FINGERS *********/
    L1A1F1 = new MatrixTransform(glm::mat4(1.0f));
    subSet1 -> addChild(L1A1F1);
    L1A1F2 = new MatrixTransform(glm::mat4(1.0f));
    subSet1 -> addChild(L1A1F2);
    L1A1F3 = new MatrixTransform(glm::mat4(1.0f));
    subSet1 -> addChild(L1A1F3);
    L1A2F1 = new MatrixTransform(glm::mat4(1.0f));
    subSet2 -> addChild(L1A2F1);
    L1A2F2 = new MatrixTransform(glm::mat4(1.0f));
    subSet2 -> addChild(L1A2F2);
    L1A2F3 = new MatrixTransform(glm::mat4(1.0f));
    subSet2 -> addChild(L1A2F3);
    L1A3F1 = new MatrixTransform(glm::mat4(1.0f));
    subSet3 -> addChild(L1A3F1);
    L1A3F2 = new MatrixTransform(glm::mat4(1.0f));
    subSet3 -> addChild(L1A3F2);
    L1A3F3 = new MatrixTransform(glm::mat4(1.0f));
    subSet3 -> addChild(L1A3F3);
    /******************************************/
    
    /******* LEVEL 1-- ARM123 -- FINGERS 1-9 -- PODS ******/
    L1pod_1 = new MatrixTransform(glm::mat4(1.0f));
    L1A1F1 -> addChild(L1pod_1);
    L1pod_2 = new MatrixTransform(glm::mat4(1.0f));
    L1A1F2 -> addChild(L1pod_2);
    L1pod_3 = new MatrixTransform(glm::mat4(1.0f));
    L1A1F3 -> addChild(L1pod_3);
    L1pod_4 = new MatrixTransform(glm::mat4(1.0f));
    L1A2F1 -> addChild(L1pod_4);
    L1pod_5 = new MatrixTransform(glm::mat4(1.0f));
    L1A2F2 -> addChild(L1pod_5);
    L1pod_6 = new MatrixTransform(glm::mat4(1.0f));
    L1A2F3 -> addChild(L1pod_6);
    L1pod_7 = new MatrixTransform(glm::mat4(1.0f));
    L1A3F1 -> addChild(L1pod_7);
    L1pod_8 = new MatrixTransform(glm::mat4(1.0f));
    L1A3F2 -> addChild(L1pod_8);
    
    MatrixTransform * L1pod_9 = new MatrixTransform(glm::mat4(1.0f));
    L1A3F3 -> addChild(L1pod_9);
    /**********************/
    
    /************************* LEVEL 2 ***********************/
    //level 2 -- arm set
    L2setA = new MatrixTransform(glm::mat4(1.0f));
    level2->addChild(L2setA);
    
    //level 2 --arm root nodes
    L2arm_1 = new MatrixTransform(glm::mat4(1.0f));
    L2setA ->addChild(L2arm_1);
    L2arm_2 = new MatrixTransform(glm::mat4(1.0f));
    L2setA ->addChild(L2arm_2);
    L2arm_3 = new MatrixTransform(glm::mat4(1.0f));
    L2setA ->addChild(L2arm_3);
    
    //level 2 finger set
     L2fingerset1 = new MatrixTransform(glm::mat4 (1.0f));
    L2arm_1->addChild(L2fingerset1);
    L2fingerset2 = new MatrixTransform(glm::mat4 (1.0f));
    L2arm_2->addChild(L2fingerset2);
  L2fingerset3 = new MatrixTransform(glm::mat4 (1.0f));
    L2arm_3->addChild(L2fingerset3);
    
    //level 2 finger nodes
   MatrixTransform *  L2A1F1 = new MatrixTransform(glm::mat4(1.0f));
    L2fingerset1 -> addChild(L2A1F1);
  MatrixTransform *    L2A1F2 = new MatrixTransform(glm::mat4(1.0f));
    L2fingerset1 -> addChild(L2A1F2);
  MatrixTransform *    L2A1F3 = new MatrixTransform(glm::mat4(1.0f));
    L2fingerset1 -> addChild(L2A1F3);
   MatrixTransform *   L2A2F1 = new MatrixTransform(glm::mat4(1.0f));
    L2fingerset2 -> addChild(L2A2F1);
  MatrixTransform *    L2A2F2 = new MatrixTransform(glm::mat4(1.0f));
    L2fingerset2 -> addChild(L2A2F2);
  MatrixTransform *    L2A2F3 = new MatrixTransform(glm::mat4(1.0f));
    L2fingerset2 -> addChild(L2A2F3);
   MatrixTransform *   L2A3F1 = new MatrixTransform(glm::mat4(1.0f));
    L2fingerset3 -> addChild(L2A3F1);
   MatrixTransform *   L2A3F2 = new MatrixTransform(glm::mat4(1.0f));
    L2fingerset3 -> addChild(L2A3F2);
  MatrixTransform *    L2A3F3 = new MatrixTransform(glm::mat4(1.0f));
    L2fingerset3 -> addChild(L2A3F3);
    
    //level 2 pods
  MatrixTransform *    L2A1F1pod_1 = new MatrixTransform(glm::mat4(1.0f));
    L2A1F1 -> addChild(L2A1F1pod_1);
  MatrixTransform *    L2A1F2pod_2 = new MatrixTransform(glm::mat4(1.0f));
    L2A1F2 -> addChild(L2A1F2pod_2);
 MatrixTransform *     L2A1F3pod_3 = new MatrixTransform(glm::mat4(1.0f));
    L2A1F3 -> addChild(L2A1F3pod_3);
 MatrixTransform *     L2A2F4pod_4 = new MatrixTransform(glm::mat4(1.0f));
    L2A2F1 -> addChild(L2A2F4pod_4);
 MatrixTransform *     L2A2F5pod_5 = new MatrixTransform(glm::mat4(1.0f));
    L2A2F2 -> addChild(L2A2F5pod_5);
 MatrixTransform *     L2A2F6pod_6 = new MatrixTransform(glm::mat4(1.0f));
    L2A2F3 -> addChild(L2A2F6pod_6);
 MatrixTransform *     L2A3F7pod_7 = new MatrixTransform(glm::mat4(1.0f));
    L2A3F1 -> addChild(L2A3F7pod_7);
 MatrixTransform *     L2A3F8pod_8 = new MatrixTransform(glm::mat4(1.0f));
    L2A3F2 -> addChild(L2A3F8pod_8);
 MatrixTransform *     L2A3F9pod_9 = new MatrixTransform(glm::mat4(1.0f));
    L2A3F3 -> addChild(L2A3F9pod_9);
    
    /****************/
    /********* LEVEL 3 -- ARM SET 1 **********/
    set3 = new MatrixTransform (glm::mat4(1.0f));
    level3->addChild(set3);
    /*****************************************/
    
    /************ LEVEL 1- ARMS *************/
    //level 1--arm root node
  L3arm_1 = new MatrixTransform(glm::mat4(1.0f));
    set3 ->addChild(L3arm_1);
  L3arm_2 = new MatrixTransform(glm::mat4(1.0f));
    set3 ->addChild(L3arm_2);
 L3arm_3 = new MatrixTransform(glm::mat4(1.0f));
    set3 ->addChild(L3arm_3);
    /*******************************************/
    
    /************** LEVEL 1 -- FINGER SET *********/
 L3subSet1 = new MatrixTransform(glm::mat4(1.0f));
    L3arm_1 -> addChild(L3subSet1);
  L3subSet2 = new MatrixTransform(glm::mat4(1.0f));
    L3arm_2 -> addChild(L3subSet2);
  L3subSet3 = new MatrixTransform(glm::mat4(1.0f));
    L3arm_3 -> addChild(L3subSet3);
    /************************************************/
    
    /******** LEVEL 1 -- ARM 123 ---- FINGERS *********/
MatrixTransform*    L3A1F1 = new MatrixTransform(glm::mat4(1.0f));
    L3subSet1 -> addChild(L3A1F1);
 MatrixTransform*   L3A1F2 = new MatrixTransform(glm::mat4(1.0f));
    L3subSet1 -> addChild(L3A1F2);
 MatrixTransform*   L3A1F3 = new MatrixTransform(glm::mat4(1.0f));
    L3subSet1 -> addChild(L3A1F3);
 MatrixTransform*   L3A2F1 = new MatrixTransform(glm::mat4(1.0f));
    L3subSet2 -> addChild(L3A2F1);
 MatrixTransform*   L3A2F2 = new MatrixTransform(glm::mat4(1.0f));
    L3subSet2 -> addChild(L3A2F2);
 MatrixTransform*   L3A2F3 = new MatrixTransform(glm::mat4(1.0f));
    L3subSet2 -> addChild(L3A2F3);
 MatrixTransform*   L3A3F1 = new MatrixTransform(glm::mat4(1.0f));
    L3subSet3 -> addChild(L3A3F1);
MatrixTransform*    L3A3F2 = new MatrixTransform(glm::mat4(1.0f));
    L3subSet3 -> addChild(L3A3F2);
 MatrixTransform*   L3A3F3 = new MatrixTransform(glm::mat4(1.0f));
    L3subSet3 -> addChild(L3A3F3);
    /******************************************/
    
    /******* LEVEL 1-- ARM123 -- FINGERS 1-9 -- PODS ******/
 MatrixTransform*   L3A1F1pod_1 = new MatrixTransform(glm::mat4(1.0f));
    L3A1F1 -> addChild(L3A1F1pod_1);
MatrixTransform*    L3A1F2pod_2 = new MatrixTransform(glm::mat4(1.0f));
    L3A1F2 -> addChild(L3A1F2pod_2);
 MatrixTransform*   L3A1F3pod_3 = new MatrixTransform(glm::mat4(1.0f));
    L3A1F3 -> addChild(L3A1F3pod_3);
 MatrixTransform*   L3A2F4pod_4 = new MatrixTransform(glm::mat4(1.0f));
    L3A2F1 -> addChild(L3A2F4pod_4);
MatrixTransform*    L3A2F5pod_5 = new MatrixTransform(glm::mat4(1.0f));
    L3A2F2 -> addChild(L3A2F5pod_5);
MatrixTransform*    L3A2F6pod_6 = new MatrixTransform(glm::mat4(1.0f));
    L3A2F3 -> addChild(L3A2F6pod_6);
MatrixTransform*    L3A3F7pod_7 = new MatrixTransform(glm::mat4(1.0f));
    L3A3F1 -> addChild(L3A3F7pod_7);
MatrixTransform*    L3A3F8pod_8 = new MatrixTransform(glm::mat4(1.0f));
    L3A3F2 -> addChild(L3A3F8pod_8);
MatrixTransform*    L3A3F9pod_9 = new MatrixTransform(glm::mat4(1.0f));
    L3A3F3 -> addChild(L3A3F9pod_9);
    /**********************/
    

    
    /************** CENTER POLES: SHOWS LEVELS **********************/
    //center poles
    result = calcMT(0.0f, glm::vec3(0.5f,4.5f, 0.5f), glm::vec3(1.0f,2.5f, 1.0f)  ,glm::vec3(0.0f, 0.0f, 0.0f));
    m_cyl1 = new MatrixTransform(result);
    m_cyl1->addChild(geoCylinder);
    level1->addChild(m_cyl1);
    
    product = calcMT(  0.0f, glm::vec3(0.5f,4.5f, 0.5f),glm::vec3(1.0f,2.5f, 1.0f),glm::vec3(0.0f, -10.0f, 0.0f));
    m_cyl2 = new MatrixTransform(product);
    m_cyl2 -> addChild(geoCylinder2);
    level2->addChild(m_cyl2);
    
    product = calcMT(0.0f,  glm::vec3(0.5f,4.5f, 0.5f), glm::vec3(1.0f,2.5f, 1.0f),glm::vec3(0.0f, -30.0f, 0.0f));
    MatrixTransform * m_cyl3 = new MatrixTransform(product);
    m_cyl3 -> addChild(geoCylinder3);
    level3->addChild(m_cyl3);
    
    //main pole::UNMOVABLE
    product = calcMT(0.0f,  glm::vec3(0.5f,4.5f, 0.5f), glm::vec3(1.0f,29.0f, 1.0f),glm::vec3(0.0f, 0.0f, 0.0f));
    MatrixTransform * main_cylinder = new MatrixTransform(product);
    main_cylinder -> addChild(mainCGeo);
    m_root->addChild(main_cylinder);
//    /**************************************************/
//    
//    /********* LEVEL 1 ***********/
//    /***************** ARMS **********************/
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,3.0f,9.0f));
    L1A1 = new MatrixTransform(product);
    L1A1->addChild(geoArm1);
    L1arm_1 ->addChild(L1A1);
    
    //fake
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,3.0f,9.0f));
    MatrixTransform* L1A1fake = new MatrixTransform(product);
    L1A1fake->addChild(geoArm1F);
    set1->addChild(L1A1fake);

    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,3.0f,9.0f));
    product = glm::rotate(glm::mat4 (1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    L1A2 = new MatrixTransform(product);
    L1A2 -> addChild(geoArm2);
    L1arm_3 -> addChild(L1A2);
    
    //fake
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,3.0f,9.0f));
    product = glm::rotate(glm::mat4 (1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
   MatrixTransform *  L1A2fake = new MatrixTransform(product);
    L1A2fake->addChild(geoArm2F);
    set1->addChild(L1A2fake);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,3.0f,9.0f));
    product = glm::rotate(glm::mat4 (1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    L1A3 = new MatrixTransform(product);
    L1A3->addChild(geoArm3);
    L1arm_2->addChild(L1A3);
    
    //fake
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,3.0f,9.0f));
    product = glm::rotate(glm::mat4 (1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
   MatrixTransform *  L1A3fake = new MatrixTransform(product);
    L1A3fake->addChild(geoArm3F);
    set1->addChild(L1A3fake);
    
    
//    /*****************************************/
//    /*================ FINGERS SET: LEVEL 1-- ARM1 =================*/
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,4.0f,24.0f));
   MatrixTransform*  L1A1finger1 = new MatrixTransform(product);
    L1A1finger1->addChild(geoSubArm1);
    L1A1F1->addChild(L1A1finger1);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,4.0f,24.0f));
    product = glm::rotate(glm::mat4(1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (-15.0f, 0.0f, 28.0f)) * product;
  MatrixTransform*  L1A1finger2 = new MatrixTransform(product);
    L1A1finger2->addChild(geoSubArm2);
    L1A1F2->addChild(L1A1finger2);
//
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,4.0f,24.0f));
    product = glm::rotate(glm::mat4(1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (15.0f, 0.0f, 28.0f)) * product;
   MatrixTransform *  L1A1finger3 = new MatrixTransform(product);
    L1A1finger3->addChild(geoSubArm3);
    L1A1F3->addChild(L1A1finger3);
//
////    /*~~~~~~~~~~ PODS : LEVEL 1 ~~~~~~~~*/
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 4.0f,31.0f));
    MatrixTransform * L1A1F1p1 = new MatrixTransform(product);
    L1A1F1p1->addChild(geoPodL1A1);
    L1pod_1->addChild(L1A1F1p1);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(0.0f, 4.0f,31.0f));
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (-11.0f, 0.0f, -16.0f)) * product;
    MatrixTransform * L1A1F1p2 = new MatrixTransform(product);
    L1A1F1p2->addChild(geoPodL1A2);
    L1pod_2->addChild(L1A1F1p2);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(0.0f, 4.0f,31.0f));
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (10.0f, 0.0f, -16.0f)) * product;
    MatrixTransform * L1A1F1p3 = new MatrixTransform(product);
    L1A1F1p3->addChild(geoPodL1A3);
    L1pod_3->addChild(L1A1F1p3);
    
//
//    /*================ Fingers SET2: LEVEL 1-- ARM2 =================*/
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(-15.0f,4.0f,-15.0f));
   MatrixTransform *  L1A2finger1 = new MatrixTransform(product);
    L1A2finger1->addChild(geoSubArm4);
    L1A2F1->addChild(L1A2finger1);

    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(-15.0f,4.0f,-15.0f));
    product = glm::rotate(glm::mat4(1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (-14.0f, 0.0f, -26.0f)) * product;
   MatrixTransform *  L1A2finger2 = new MatrixTransform(product);
    L1A2finger2->addChild(geoSubArm5);
    L1A2F2->addChild(L1A2finger2);
//
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(-15.0f,4.0f,-15.0f));
    product = glm::rotate(glm::mat4(1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (-42.0f, 0.0f, -6.0f)) * product;
   MatrixTransform *  L1A2finger3 = new MatrixTransform(product);
    L1A2finger3->addChild(geoSubArm6);
    L1A2F3->addChild(L1A2finger3);
    
//    /*~~~~~~~~~~ PODS : LEVEL 1--subarm2 ~~~~~~~~*/
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(-27.0f,4.0f,-14.0f));
    L1A2F1p1 = new MatrixTransform(product);
    L1A2F1p1->addChild(geosub2PodL1A1);
    L1pod_4->addChild(L1A2F1p1);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(-27.0f,4.0f,-14.0f));
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (3.0f, 0.0f, 12.0f)) * product;
    L1A2F1p2 = new MatrixTransform(product);
    L1A2F1p2->addChild(geosub2PodL1A2);
    L1pod_5->addChild(L1A2F1p2);
//
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(-27.0f,4.0f,-14.0f));
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (11.0f, 0.0f, -7.0f)) * product;
   MatrixTransform * L1A2F1p3 = new MatrixTransform(product);
    L1A2F1p3->addChild(geosub2PodL1A3);
    L1pod_6->addChild(L1A2F1p3);
//
//    /*================ SUBARM SET2: LEVEL 1-- ARM3 =================*/

    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(16.0f,4.0f,-15.0f));
   MatrixTransform *  L1A3finger1 = new MatrixTransform(product);
    L1A3finger1->addChild(geoSubArm7);
    L1A3F1->addChild(L1A3finger1);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,4.0f,0.0f));
    product = glm::rotate(glm::mat4(1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (21.0f, 0.0f, -11.0f)) * product;
  MatrixTransform * L1A3finger2 = new MatrixTransform(product);
    L1A3finger2->addChild(geoSubArm8);
    L1A3F2->addChild(L1A3finger2);

    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,4.0f,0.0f));
    product = glm::rotate(glm::mat4(1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (21.0f, 0.0f, -5.0f)) * product;
 MatrixTransform * L1A3finger3 = new MatrixTransform(product);
    L1A3finger3->addChild(geoSubArm9);
    L1A3F3->addChild(L1A3finger3);
//
//    /*~~~~~~~~~~ PODS : LEVEL 1--ARM3 ~~~~~~~~*/
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(27.0f,4.0f,-3.0f));
    L1A3F1p1 = new MatrixTransform(product);
    L1A3F1p1->addChild(geoL1A3F1p1);
    L1pod_7->addChild(L1A3F1p1);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(25.0f,4.0f,-14.0f));
    L1A3F1p2 = new MatrixTransform(product);
    L1A3F1p2->addChild(geoL1A3F2p2);
    L1pod_8->addChild(L1A3F1p2);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(17.0f,4.0f,-20.0f));
    L1A3F3p3 = new MatrixTransform(product);
    L1A3F3p3->addChild(geoL1A3F3p3);
    L1pod_9->addChild(L1A3F3p3);

//    /**********LEVEL 2*************/
//    /***************** level 2 -- center ARMS **********************/
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,-7.0f,9.0f));
    MatrixTransform *  L2A1 = new MatrixTransform(product);
    L2A1->addChild(L2geoArm1);
    L2arm_1->addChild(L2A1);

    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,-7.0f,9.0f));
    product = glm::rotate(glm::mat4 (1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
      MatrixTransform * L2A2 = new MatrixTransform(product);
    L2A2->addChild(L2geoArm2);
    L2arm_3->addChild(L2A2);
//
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,-7.0f,9.0f));
    product = glm::rotate(glm::mat4 (1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
      MatrixTransform * L2A3 = new MatrixTransform(product);
    L2A3->addChild(L2geoArm3);
    L2arm_2->addChild(L2A3);
    
    //fakes
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,-7.0f,9.0f));
    MatrixTransform *  L2A1_fake = new MatrixTransform(product);
    L2A1_fake->addChild(L2geoArm1_fake);
    L2setA->addChild(L2A1_fake);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,-7.0f,9.0f));
    product = glm::rotate(glm::mat4 (1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    MatrixTransform * L2A2_fake = new MatrixTransform(product);
    L2A2_fake->addChild(L2geoArm2_fake);
    L2setA->addChild(L2A2_fake);
    //
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,-7.0f,9.0f));
    product = glm::rotate(glm::mat4 (1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    MatrixTransform * L2A3_fake = new MatrixTransform(product);
    L2A3_fake->addChild(L2geoArm3_fake);
    L2setA->addChild(L2A3_fake);


//   /*****************************************/
//   /*================ FINGERS SET: LEVEL 2-- ARM1 =================*/
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,-6.0f,24.0f));
      MatrixTransform * L2A1Finger1 = new MatrixTransform(product);
    L2A1Finger1->addChild(L2geoSubArm1);
    L2A1F1->addChild(L2A1Finger1);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,-6.0f,24.0f));
    product = glm::rotate(glm::mat4(1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (-15.0f, 0.0f, 28.0f)) * product;
     MatrixTransform *  L2A1finger2 = new MatrixTransform(product);
    L2A1finger2->addChild(L2geoSubArm2);
    L2A1F2->addChild(L2A1finger2);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,-6.0f,24.0f));
    product = glm::rotate(glm::mat4(1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (15.0f, 0.0f, 28.0f)) * product;
     MatrixTransform *  L2A1finger3 = new MatrixTransform(product);
    L2A1finger3->addChild(L2geoSubArm3);
    L2A1F3->addChild(L2A1finger3);
    
//    ///*~~~~~~~~~~ PODS -- a1 : LEVEL 2 ~~~~~~~~*/
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, -6.0f,31.0f));
   MatrixTransform * L2A1F1p1 = new MatrixTransform(product);
    L2A1F1p1->addChild(L2geoPodL1A1);
    L2A1F1pod_1->addChild(L2A1F1p1);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(0.0f, -6.0f,31.0f));
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (-11.0f, 0.0f, -16.0f)) * product;
   MatrixTransform * L2A1F1p2 = new MatrixTransform(product);
    L2A1F1p2->addChild(L2geoPodL1A2);
    L2A1F2pod_2->addChild(L2A1F1p2);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(0.0f, -6.0f,31.0f));
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (10.0f, 0.0f, -16.0f)) * product;
   MatrixTransform * L2A1F1p3 = new MatrixTransform(product);
    L2A1F1p3->addChild(L2geoPodL1A3);
    L2A1F3pod_3->addChild(L2A1F1p3);
    
////    /*================ Finger SET2: LEVEL 1-- ARM2 =================*/
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(-15.0f,-6.0f,-15.0f));
   MatrixTransform*  L2A2finger1 = new MatrixTransform(product);
    L2A2finger1->addChild(L2geoSubArm4);
    L2A2F1->addChild(L2A2finger1);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(-15.0f,-6.0f,-15.0f));
    product = glm::rotate(glm::mat4(1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (-14.0f, 0.0f, -26.0f)) * product;
    MatrixTransform*  L2A2finger2 = new MatrixTransform(product);
    L2A2finger2->addChild(L2geoSubArm5);
    L2A2F2->addChild(L2A2finger2);

    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(-15.0f,-6.0f,-15.0f));
    product = glm::rotate(glm::mat4(1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (-42.0f, 0.0f, -6.0f)) * product;
     MatrixTransform* L2A2finger3 = new MatrixTransform(product);
    L2A2finger3->addChild(L2geoSubArm6);
    L2A2F3->addChild(L2A2finger3);
    
////    /*~~~~~~~~~~ PODS : LEVEL 2--subarm2 ~~~~~~~~*/
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(-27.0f,-6.0f,-14.0f));
    MatrixTransform *  L2A2F1p1 = new MatrixTransform(product);
    L2A2F1p1->addChild(L2geosub2PodL1A1);
    L2A2F4pod_4->addChild(L2A2F1p1);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(-27.0f,-6.0f,-14.0f));
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (3.0f, 0.0f, 12.0f)) * product;
   MatrixTransform *   L2A2F1p2 = new MatrixTransform(product);
    L2A2F1p2->addChild(L2geosub2PodL1A2);
    L2A2F5pod_5->addChild(L2A2F1p2);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(-27.0f,-6.0f,-14.0f));
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (11.0f, 0.0f, -7.0f)) * product;
    MatrixTransform *  L2A2F1p3 = new MatrixTransform(product);
    L2A2F1p3->addChild(L2geosub2PodL1A3);
    L2A2F6pod_6->addChild(L2A2F1p3);

    /*================ SUBARM SET2: LEVEL 2-- ARM3 =================*/
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(16.0f,-6.0f,-15.0f));
   MatrixTransform*  L2A3finger1 = new MatrixTransform(product);
    L2A3finger1->addChild(L2geoSubArm7);
    L2A3F1->addChild(L2A3finger1);

    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,-6.0f, 0.0f));
    product = glm::rotate(glm::mat4(1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
     product = glm::translate(glm::mat4(1.0f), glm::vec3 (21.0f, 0.0f, -11.0f)) * product;
    MatrixTransform*   L2A3finger2 = new MatrixTransform(product);
    L2A3finger2->addChild(L2geoSubArm8);
    L2A3F2->addChild(L2A3finger2);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,-6.0f,0.0f));
    product = glm::rotate(glm::mat4(1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (21.0, 0.0f, -5.0f)) * product;
    MatrixTransform*   L2A3finger3 = new MatrixTransform(product);
    L2A3finger3->addChild(L2geoSubArm9);
    L2A3F3->addChild(L2A3finger3);
    
   /*~~~~~~~~~~ PODS : LEVEL 1--ARM3 ~~~~~~~~*/
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(27.0f,-6.0f,-3.0f));
   MatrixTransform *  L2A3F1p1 = new MatrixTransform(product);
    L2A3F1p1->addChild(L2geoL1A3F1p1);
    L2A3F7pod_7->addChild(L2A3F1p1);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(25.0f,-6.0f,-14.0f));
   MatrixTransform *  L2A3F1p2 = new MatrixTransform(product);
    L2A3F1p2->addChild(L2geoL1A3F2p2);
    L2A3F8pod_8->addChild(L2A3F1p2);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(17.0f,-6.0f,-20.0f));
   MatrixTransform *  L2A3F1p3 = new MatrixTransform(product);
    L2A3F1p3->addChild(L2geoL1A3F3p3);
    L2A3F9pod_9->addChild(L2A3F1p3);
    
    /****************** Level 3 *******************/

    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,-27.0f,9.0f));
    MatrixTransform *  L3A1 = new MatrixTransform(product);
    L3A1->addChild(L3geoArm1);
    L3arm_1->addChild(L3A1);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,-27.0f,9.0f));
    product = glm::rotate(glm::mat4 (1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    MatrixTransform * L3A2 = new MatrixTransform(product);
    L3A2->addChild(L3geoArm2);
    L3arm_3->addChild(L3A2);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,-27.0f,9.0f));
    product = glm::rotate(glm::mat4 (1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    MatrixTransform * L3A3 = new MatrixTransform(product);
    L3A3->addChild(L3geoArm3);
    L3arm_2->addChild(L3A3);
    
    //fake
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,-27.0f,9.0f));
    MatrixTransform *  L3A1_fake = new MatrixTransform(product);
    L3A1_fake->addChild(L3geoArm1_fake);
    set3->addChild(L3A1_fake);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,-27.0f,9.0f));
    product = glm::rotate(glm::mat4 (1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    MatrixTransform * L3A2_fake = new MatrixTransform(product);
    L3A2_fake->addChild(L3geoArm2_fake);
    set3->addChild(L3A2_fake);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 10.0f), glm::vec3(0.0f,-27.0f,9.0f));
    product = glm::rotate(glm::mat4 (1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    MatrixTransform * L3A3_fake = new MatrixTransform(product);
    L3A3_fake->addChild(L3geoArm3_fake);
    set3->addChild(L3A3_fake);
    
    /*****************************************/
    /*================ FINGERS SET: LEVEL 3-- ARM1 =================*/
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,-26.0f,24.0f));
    MatrixTransform * L3A1Finger1 = new MatrixTransform(product);
    L3A1Finger1->addChild(L3geoSubArm1);
    L3A1F1->addChild(L3A1Finger1);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,-26.0f,24.0f));
    product = glm::rotate(glm::mat4(1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (-15.0f, 0.0f, 28.0f)) * product;
    MatrixTransform *  L3A1finger2 = new MatrixTransform(product);
    L3A1finger2->addChild(L3geoSubArm2);
    L3A1F2->addChild(L3A1finger2);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,-26.0f,24.0f));
    product = glm::rotate(glm::mat4(1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (15.0f, 0.0f, 28.0f)) * product;
    MatrixTransform *  L3A1finger3 = new MatrixTransform(product);
    L3A1finger3->addChild(L3geoSubArm3);
    L3A1F3->addChild(L3A1finger3);

    ///*~~~~~~~~~~ PODS -- a1 : LEVEL 3 ~~~~~~~~*/
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, -26.0f,31.0f));
    MatrixTransform * L3A1F1p1 = new MatrixTransform(product);
    L3A1F1p1->addChild(L3geoPodL1A1);
    L3A1F1pod_1->addChild(L3A1F1p1);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(0.0f, -26.0f,31.0f));
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (-11.0f, 0.0f, -16.0f)) * product;
    MatrixTransform * L3A1F1p2 = new MatrixTransform(product);
    L3A1F1p2->addChild(L3geoPodL1A2);
    L3A1F2pod_2->addChild(L3A1F1p2);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(0.0f, -26.0f,31.0f));
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (10.0f, 0.0f, -16.0f)) * product;
    MatrixTransform * L3A1F1p3 = new MatrixTransform(product);
    L3A1F1p3->addChild(L3geoPodL1A3);
    L3A1F3pod_3->addChild(L3A1F1p3);
    
        /*================ Finger SET2: LEVEL 1-- ARM2 =================*/
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(-15.0f,-26.0f,-15.0f));
    MatrixTransform*  L3A2finger1 = new MatrixTransform(product);
    L3A2finger1->addChild(L3geoSubArm4);
    L3A2F1->addChild(L3A2finger1);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(-15.0f,-26.0f,-15.0f));
    product = glm::rotate(glm::mat4(1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (-14.0f, 0.0f, -26.0f)) * product;
    MatrixTransform*  L3A2finger2 = new MatrixTransform(product);
    L3A2finger2->addChild(L3geoSubArm5);
    L3A2F2->addChild(L3A2finger2);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 5.0f), glm::vec3(-15.0f,-26.0f,-15.0f));
    product = glm::rotate(glm::mat4(1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (-42.0f, 0.0f, -6.0f)) * product;
    MatrixTransform* L3A2finger3 = new MatrixTransform(product);
    L3A2finger3->addChild(L3geoSubArm6);
    L3A2F3->addChild(L3A2finger3);
    
    //    /*~~~~~~~~~~ PODS : LEVEL 3--subarm2 ~~~~~~~~*/
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(-27.0f,-26.0f,-14.0f));
    MatrixTransform *  L3A2F1p1 = new MatrixTransform(product);
    L3A2F1p1->addChild(L3geosub2PodL1A1);
    L3A2F4pod_4->addChild(L3A2F1p1);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(-27.0f,-26.0f,-14.0f));
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (3.0f, 0.0f, 12.0f)) * product;
    MatrixTransform *   L3A2F1p2 = new MatrixTransform(product);
    L3A2F1p2->addChild(L3geosub2PodL1A2);
    L3A2F5pod_5->addChild(L3A2F1p2);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(-27.0f,-26.0f,-14.0f));
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (11.0f, 0.0f, -7.0f)) * product;
    MatrixTransform *  L3A2F1p3 = new MatrixTransform(product);
    L3A2F1p3->addChild(L3geosub2PodL1A3);
    L3A2F6pod_6->addChild(L3A2F1p3);
    
    /*================ SUBARM SET2: LEVEL 3-- ARM3 =================*/
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(16.0f,-26.0f,-15.0f));
    MatrixTransform*  L3A3finger1 = new MatrixTransform(product);
    L3A3finger1->addChild(L3geoSubArm7);
    L3A3F1->addChild(L3A3finger1);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,-26.0f,0.0f));
    product = glm::rotate(glm::mat4(1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (21.0f, 0.0f, -11.0f)) * product;
    MatrixTransform*   L3A3finger2 = new MatrixTransform(product);
    L3A3finger2->addChild(L3geoSubArm8);
    L3A3F2->addChild(L3A3finger2);
    
    product = calcMT((90.0f/180.0f) * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 6.0f), glm::vec3(0.0f,-26.0f,0.0f));
    product = glm::rotate(glm::mat4(1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * product;
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (21.0, 0.0f, -5.0f)) * product;
    MatrixTransform*   L3A3finger3 = new MatrixTransform(product);
    L3A3finger3->addChild(L3geoSubArm9);
    L3A3F3->addChild(L3A3finger3);
    
    //    /*~~~~~~~~~~ PODS : LEVEL 1--ARM3 ~~~~~~~~*/
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(27.0f,-26.0f,-3.0f));
    MatrixTransform *  L3A3F1p1 = new MatrixTransform(product);
    L3A3F1p1->addChild(L3geoL1A3F1p1);
    L3A3F7pod_7->addChild(L3A3F1p1);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(25.0f,-26.0f,-14.0f));
    MatrixTransform *  L3A3F1p2 = new MatrixTransform(product);
    L3A3F1p2->addChild(L3geoL1A3F2p2);
    L3A3F8pod_8->addChild(L3A3F1p2);
    
    product = calcMT(0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f,2.0f),glm::vec3(17.0f,-26.0f,-20.0f));
    MatrixTransform *  L3A3F1p3 = new MatrixTransform(product);
    L3A3F1p3->addChild(L3geoL1A3F3p3);
    L3A3F9pod_9->addChild(L3A3F1p3);
    
    //bear
    product = glm::scale(glm::mat4(1.0f), glm::vec3(0.10f, 0.10f, 0.10f));
    product = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, -0.3f, 0.3f)) * product;
    bearO = new MatrixTransform(product);
    bearO->addChild(beargeo);
    L3A3F1p3->addChild(bearO);

/***************************************************************************/
}
//multi transform
glm::mat4 Window::calcMT(float angle, glm::vec3 rot , glm::vec3 scale, glm::vec3 trans){
    
    glm::mat4 multi  = glm::mat4(1.0f);
    multi = glm::rotate(glm::mat4(1.0f), angle, rot) * multi;
    multi = glm::scale(glm::mat4(1.0f), scale) * multi;
    multi = glm::translate(glm::mat4(1.0f), trans) * multi;
    
    return multi;
}
//which arm
glm::mat4 Window::armCalc (float angle, glm::vec3 rot , glm::vec3 scale, glm::vec3 trans){
    
    glm::mat4 multi  = glm::mat4(1.0f);
    multi = glm::translate(glm::mat4(1.0f), trans) * multi;
    multi = glm::rotate(glm::mat4(1.0f), angle, rot) * multi;
    multi = glm::scale(glm::mat4(1.0f), scale) * multi;

    return multi;
}

glm::mat4 Window::podCalc (float angle, glm::vec3 rot , glm::vec3 scale, glm::vec3 trans){
    
    glm::mat4 multi  = glm::mat4(1.0f);
    multi = glm::rotate(glm::mat4(1.0f), angle, rot) * multi;
    multi = glm::scale(glm::mat4(1.0f), scale) * multi;
    multi = glm::translate(glm::mat4(1.0f), trans) * multi;
    
    return multi;
}


void Window::clean_up()
{
	delete(cubemap);
	glDeleteProgram(shaderProgram);
    glDeleteProgram(skyboxShader);
}

GLFWwindow* Window::create_window(int width, int height)
{
    printf("Window::create_window()\n");
    
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
	Window::width = width;
	Window::height = height;
	// Set the viewport size
	
    glViewport(0, 0, width, height);

	if (height > 0)
	{
		P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}
    
}


void Window::idle_callback()
{
    
   // beargeo -> spin();
    
    if(bearOn){
        
        glm::mat4 rotation = glm::mat4(glm::mat3(beargeo->M));
        rotation = glm::transpose(rotation);
        
        glm::vec3 position = glm::vec3 (beargeo->M[3]);
        position = - position + glm::vec3(-0.59f,-4.5f , 0.7f);
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
        
        V = rotation * translation;
        bearV = rotation * translation;
    }

    
    //only updating children
    m_root ->update(glm::mat4(1.0f));
    
    //animating it
    //center poles: bounce
    ylev = ylev + offset;
    if(ylev >= 5.0f ){
        offset = -offset;
    }
    else if (ylev<= - 5.0f ){
        offset = -offset;
    }
   
    //rot_angle
    if(rot_angle >= 360.0f){
        rot_offset = 0.0f;
    }
    rot_angle = rot_angle + rot_offset;
    
    extend += eOffset;
    if(extend >= 10.0f)
        eOffset = -eOffset;
    else if (extend <= 0.0f)
        eOffset = -eOffset;
    
    //rotate ride
    m_root->M =glm::rotate(glm::mat4(1.0f), rot_angle-0.5f, glm::vec3(0.0f, 1.0f,0.0f));
   
    //move center pillars up and down
    level1->M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, ylev + 5.0f, 0.0f));
    level2->M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, ylev , 0.0f));
    level3->M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, ylev +5.0f, 0.0f));

    //Animate rot: set
    set1-> M =glm::rotate(glm::mat4(1.0f), rot_angle, glm::vec3(0.0f, 1.0f,0.0f));
    L2setA->M =glm::rotate(glm::mat4(1.0f), rot_angle, glm::vec3(0.0f, 1.0f,0.0f));
    set3->M =glm::rotate(glm::mat4(1.0f), rot_angle, glm::vec3(0.0f, 1.0f,0.0f));

    /***** above is done ******/
    
    //level 1--animate rot finger sets
    //M = T * R * T_inverse;
    subSet1->M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 4.0f, 20.0f)) * glm::rotate(glm::mat4(1.0f), rot_angle, glm::vec3(0.0f, 1.0f, 0.0f))* glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -4.0f, -20.0f));
    //off--x value
    subSet2->M = glm::translate(glm::mat4(1.0f), glm::vec3(-15.0f, 4.0f, -11.0f)) * glm::rotate(glm::mat4(1.0f), rot_angle, glm::vec3(0.0f, 1.0f, 0.0f))* glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, -4.0f, 11.0f));
    
    subSet3-> M = glm::translate(glm::mat4(1.0f), glm::vec3(17.0f, 4.0f, -11.0f)) * glm::rotate(glm::mat4(1.0f), rot_angle, glm::vec3(0.0f, 1.0f, 0.0f))* glm::translate(glm::mat4(1.0f), glm::vec3(-17.0f, -4.0f, 11.0f));
    
    //level 2
     L2fingerset1->M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -6.0f, 20.0f)) * glm::rotate(glm::mat4(1.0f), rot_angle, glm::vec3(0.0f, 1.0f, 0.0f))* glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 6.0f, -20.0f));

    L2fingerset2->M = glm::translate(glm::mat4(1.0f), glm::vec3(-15.0f, -6.0f, -11.0f)) * glm::rotate(glm::mat4(1.0f), rot_angle, glm::vec3(0.0f, 1.0f, 0.0f))* glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, 6.0f, 11.0f));
    
    L2fingerset3-> M = glm::translate(glm::mat4(1.0f), glm::vec3(17.0f, -6.0f, -11.0f)) * glm::rotate(glm::mat4(1.0f), rot_angle, glm::vec3(0.0f, 1.0f, 0.0f))* glm::translate(glm::mat4(1.0f), glm::vec3(-17.0f, 6.0f, 11.0f));
    
    //level 3
    
    L3subSet1->M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -26.0f, 20.0f)) * glm::rotate(glm::mat4(1.0f), rot_angle, glm::vec3(0.0f, 1.0f, 0.0f))* glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 26.0f, -20.0f));
    
    L3subSet2->M = glm::translate(glm::mat4(1.0f), glm::vec3(-15.0f, -26.0f, -11.0f)) * glm::rotate(glm::mat4(1.0f), rot_angle, glm::vec3(0.0f, 1.0f, 0.0f))* glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, 26.0f, 11.0f));
    
    L3subSet3-> M = glm::translate(glm::mat4(1.0f), glm::vec3(17.0f, -26.0f, -11.0f)) * glm::rotate(glm::mat4(1.0f), rot_angle, glm::vec3(0.0f, 1.0f, 0.0f))* glm::translate(glm::mat4(1.0f), glm::vec3(-17.0f, 26.0f, 11.0f));

 //   level 1 -- extend arms
    L1arm_1-> M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, extend));
    
    L1arm_2 -> M = glm::rotate(glm::mat4 (1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, extend)) * glm::rotate(glm::mat4(1.0f), -(240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    
    L1arm_3 -> M = glm::rotate(glm::mat4 (1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, extend)) * glm::rotate(glm::mat4(1.0f), -(120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

    L2arm_1 -> M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, extend));

    L2arm_2->M =  glm::rotate(glm::mat4 (1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, extend)) * glm::rotate(glm::mat4(1.0f), -(240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
   
    L2arm_3 -> M =glm::rotate(glm::mat4 (1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, extend)) * glm::rotate(glm::mat4(1.0f), -(120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    
    L3arm_1 -> M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, extend));
    
    L3arm_2->M =  glm::rotate(glm::mat4 (1.0f), (240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, extend)) * glm::rotate(glm::mat4(1.0f), -(240.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    
    L3arm_3 -> M =glm::rotate(glm::mat4 (1.0f), (120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, extend)) * glm::rotate(glm::mat4(1.0f), -(120.0f/180.0f) * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    
    //rotate pods
    for(Geode * somePod: pods ){
        somePod->spin();
    }
    
    /********************************************************************/
    //rot
    if((cur_x != prev_x && cur_y != prev_y) && (cur_x<=Window::width && cur_y <= Window::height && cur_x >=0 && cur_y >= 0)){
        
        //tutorial
        glm::vec3 direction;
        float rot_angle;
        glm::vec3 curPoint;
        glm::vec3 lastPoint;
        
        curPoint = mouseMovement(cur_x, cur_y); // Map the mouse position to a logical
        lastPoint = mouseMovement(prev_x, prev_y);
        
        // sphere location.
        direction.x = cur_x - prev_x;
        direction.y = cur_y - prev_y;
        float velocity = glm::length(direction);
        
        if(obj_rot){
            
            if(velocity > 0.0001f){
                //nothing
                
                glm::vec3 rotAxis;
                rotAxis = glm::cross( lastPoint, curPoint);
                rot_angle = velocity * 0.01f;

                cam_pos = glm::vec3(glm::rotate(glm::mat4(1.0f), rot_angle, rotAxis) * glm::vec4(cam_pos,1.0f));
//                
                V = glm::lookAt(cam_pos, cam_look_at, cam_up);
            }

        prev_x = cur_x;
        prev_y = cur_y;
        }

    }
}

void Window::display_callback(GLFWwindow* window)
{
    
    
    if(!splitscreen){
           
        // Clear the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
       // V = glm::lookAt(cam_pos, cam_look_at, cam_up);
       // bearOn = false;
        cubemap->draw(skyboxShader);
        m_root->draw();
       }
       else {
           // Clear the color and depth buffers
           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
           glViewport(0,0, width/2, height);
           
           glScissor(0, 0, width/2, height);
           P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
           V = glm::lookAt(cam_pos, cam_look_at, cam_up);

           cubemap->draw(skyboxShader);
           m_root->draw();
        
           glViewport(width/2, 0, width/2, height);
           bearOn = true;
           V = bearV;

           cubemap->draw(skyboxShader);
           m_root->draw();
    }

    
    // Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{
        if(key == GLFW_KEY_ESCAPE){
            // Close the window. This causes the program to also terminate.
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        
        if (key == GLFW_KEY_R){
        
            cubemap->skyboxWorld = glm::mat4(1.0f);
        }
        else if (key == GLFW_KEY_S && mods == GLFW_MOD_SHIFT){
            cubemap->skyboxWorld = cubemap->skyboxWorld* glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
        }
        else if (key == GLFW_KEY_S && mods != GLFW_MOD_SHIFT){
            cubemap->skyboxWorld = cubemap->skyboxWorld* glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.5f));
        }
        else if (key == GLFW_KEY_C  && mods != GLFW_MOD_SHIFT){
            bearOn = true;
        }
        else if(key == GLFW_KEY_C  && mods == GLFW_MOD_SHIFT){
            bearOn = false;
        }
        else if (key == GLFW_KEY_V && mods != GLFW_MOD_SHIFT){
            splitscreen = true;
        }
        else if (key == GLFW_KEY_V && mods == GLFW_MOD_SHIFT){
            splitscreen = false;
            V = glm::lookAt(cam_pos, cam_look_at, cam_up);
        }
        else if (key == GLFW_KEY_L && mods != GLFW_MOD_SHIFT){
            lightsOn = true;
        
        }
        else if (key == GLFW_KEY_L && mods == GLFW_MOD_SHIFT){
            lightsOn = false; 
        }
	}
}

//MY FUNCTIONS
void Window::cursor_callback(GLFWwindow* window, double x, double y){
    
    //record prev points
    cur_x = 2.0f * x;
    cur_y = 2.0f * y;
}


void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
   
    if(action == GLFW_PRESS){

        if (button == GLFW_MOUSE_BUTTON_LEFT && mods != GLFW_MOD_SHIFT){
            obj_rot = true;
        }
    }
    else{
        obj_rot = false;
    }
    
}


void Window::scroll_callback(GLFWwindow* window, double xoffset , double yoffset){
    
    scrollY = - yoffset;
    //glm::vec3 scroll(0.0f, 0.0f, -scrollY);
    
    float zoom_factor = 1.0 + scrollY * 0.005f;
    
    cam_pos = zoom_factor * cam_pos;
    V = glm::lookAt(cam_pos, cam_look_at, cam_up);
}


glm::vec3 Window::mouseMovement( int x, int y){
    glm::vec3 vector; // Vector v is the synthesized 3D position of the mouse location on the trackball
    
    double d;     // this is the depth of the mouse location: the delta between the plane through the center of the trackball and the z position of the mouse
    vector.x = (2.0f * x - Window::width) / Window::width;   // this calculates the mouse X position in trackball coordinates, which range from -1 to +1
    vector.y = (Window::height - 2.0f * y) / Window::height;   // this does the equivalent to the above for the mouse Y position
    
    vector.z = 0.0f;   // initially the mouse z position is set to zero, but this will change below
    
    d = glm::length(vector);    // this is the distance from the trackball's origin to the mouse location, without considering depth (=in the plane of the trackball's origin)
    
   // d = glm::min(1.0f, (float)glm::length(vector));
    
    d= (d<1.0f) ? d : 1.0f;   // this limits d to values of 1.0 or less to avoid square roots of negative values in the following line
    
    vector.z = glm::sqrt(1.0001f - glm::pow(d, 2.0f));  // this calculates the Z coordinate of the mouse position on the trackball, based on Pythagoras: v.z*v.z + d*d = 1*1
    
    return glm::normalize(vector); // Still need to normalize, since we only capped d, not v.
    
}
