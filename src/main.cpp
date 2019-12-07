/**
 * @author	Andrew Robert Owens, Philmo Gu
 * @date 	2019-10-15.
 * @details Organization: Biological Modeling and Visualization research group
 * University of Calgary, Calgary, AB, Canada
 *
 * Contact:	arowens [at] ucalgary.ca
 * @copyright Copyright (c) 2019 ___ALGORITHMIC_BOTANY___. All rights reserved.
 *
 * @brief
 */

#include <array>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>	//assert

 // glad beforw glfw
#include "glad/glad.h"
//
#include "GLFW/glfw3.h"

#include "common_matrices.hpp"
//#include "obj_mesh_file_io.hpp"
#include "obj_mesh.hpp"
#include "mat4f.hpp"
#include "mat3f.hpp"
#include "shader.hpp"
#include "program.hpp"
#include "triangle.hpp"
#include "vec3f.hpp"
#include "vec2f.hpp"
#include "shader_file_io.hpp"
#include "buffer_object.hpp"
#include "vertex_array_object.hpp"
#include "vbo_tools.hpp"
//#include "texture.hpp"
//#include "image.hpp"

using namespace math;
using namespace geometry;
using namespace opengl;

// GLOBAL Variables
Mat4f g_M = Mat4f::identity();
Mat4f g_V = Mat4f::identity();
Mat4f g_P = Mat4f::identity();


GLuint g_width = 1000, g_height = 1000;

// function declaration
using namespace std;

void setFrameBufferSize(GLFWwindow *window, int width, int height) {
	g_width = width;
	g_height = height;
	glViewport(0, 0, g_width, g_height);
	g_P = perspectiveProjection(30, float(g_width) / g_height, 0.01, 100.f);

}

void setKeyboard(GLFWwindow *window, int key, int scancode, int action,
	int mods) {

	// Students should try and fix:
	// g_M holds the transformation of the model
	// we keep multiplying on the left or right with new matrices
	// What effect does this have on translation/rotation/scale

	if (GLFW_KEY_LEFT == key) {
		if (GLFW_REPEAT == action || GLFW_PRESS == action) {
			g_M = rotateAboutYMatrix(5) * g_M;
		}
	}
	else if (GLFW_KEY_RIGHT == key) {
		if (GLFW_REPEAT == action || GLFW_PRESS == action) {
			g_M = rotateAboutYMatrix(-5) * g_M;
		}
	}
	else if (GLFW_KEY_UP == key) {
		if (GLFW_REPEAT == action || GLFW_PRESS == action) {
			g_M = uniformScaleMatrix(1.1) * g_M;
		}
	}
	else if (GLFW_KEY_DOWN == key) {
		if (GLFW_REPEAT == action || GLFW_PRESS == action) {
			g_M = uniformScaleMatrix(1. / 1.1) * g_M;
		}
	}
	else if (GLFW_KEY_W == key) {
		if (GLFW_REPEAT == action || GLFW_PRESS == action) {
			g_M = translateMatrix(0, 0.1, 0) * g_M;
		}
	}
	else if (GLFW_KEY_S == key) {
		if (GLFW_REPEAT == action || GLFW_PRESS == action) {
			g_M = translateMatrix(0, -0.1, 0) * g_M;
		}
	}
	else if (GLFW_KEY_D == key) {
		if (GLFW_REPEAT == action || GLFW_PRESS == action) {
			g_M = translateMatrix(0.1, 0, 0) * g_M;
		}
	}
	else if (GLFW_KEY_A == key) {
		if (GLFW_REPEAT == action || GLFW_PRESS == action) {
			g_M = translateMatrix(-0.1, 0, 0) * g_M;
		}
	}
	else if (GLFW_KEY_ESCAPE == key) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
Vec2f pixelToNDC(double xpos, double ypos){
    Vec2f out;

    float viewportSplit = g_width/2;

    out.x = (((2.0*xpos)-(2.0*viewportSplit))/g_width)-1;
    out.y = -((((2.0*ypos)-(2.0*0))/g_height)-1);

    return out;
}

void setMouseButton(GLFWwindow *window, int button, int action, int mods){

    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS){
        double xpos,ypos;

        glfwGetCursorPos(window,&xpos,&ypos);

        Vec2f NDC = pixelToNDC(xpos,ypos);
        std::cout<<"Click: "<<xpos<<","<<ypos<<endl;
        std::cout<<"NDC: "<<NDC.x<<","<<NDC.y<<endl;
    }
}



// user defined alias
opengl::Program createShaderProgram(std::string const &vertexShaderFile,
	std::string const &fragmentShaderFile) {
	using namespace opengl;
	auto vertexShaderSource = loadShaderStringFromFile(vertexShaderFile);
	auto fragmentShaderSource = loadShaderStringFromFile(fragmentShaderFile);

	std::cout << "[Log] compiling program " << vertexShaderFile << ' '
		<< fragmentShaderFile << '\n';
	return opengl::makeProgram(vertexShaderSource, fragmentShaderSource);
}

std::string glfwVersion() {
	std::ostringstream s("GLFW version: ", std::ios::in | std::ios::ate);
	// print version
	int glfwMajor, glfwMinor, glfwRevision;
	glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRevision);
	s << glfwMajor << '.' << glfwMinor << '.' << glfwRevision;
	return s.str();
}

bool loadGeometryToGPU(std::vector<Vec3f> const &vertices, GLuint vboID) {
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(
		GL_ARRAY_BUFFER,                  // destination
		sizeof(Vec3f) * vertices.size(), // size (bytes) of memcopy to GPU
		vertices.data(),                  // pointer to data (contiguous)
		GL_STATIC_DRAW                    // usage patter of the GPU buffer
	);

	return true;
}

std::vector<Vec3f> subdivideClosedCurve(std::vector<Vec3f> const & points, int depth) {
	std::vector<Vec3f> out;
	//TODO	
	return out;
}

std::vector<Vec3f> subdivideOpenCurve(std::vector<Vec3f> const & points, int depth) {
	std::vector<Vec3f> out;
	//TODO
	return out;
}

std::vector<Vec3f> chaikinSubdiv(std::vector<Vec3f> const &points){

        std::vector<Vec3f> out;

        out.push_back(points[0]);
        out.push_back(0.5*points[0] + 0.5*points[1]);

        for (int i = 1; i < points.size() - 2; i++){
            out.push_back((0.75*points[i]) + (0.25*points[i+1]));
            out.push_back((0.25*points[i]) + (0.75*points[i + 1]));
        }

        out.push_back((0.5*points[points.size()-2]) + (0.5*points[points.size()-1]));
        out.push_back(points[points.size() - 1]);

        return out;

}

int getIndex (int row, int sector, int pointSize, int sectors){
    if (sector == sectors){
        return row;
    }
    else {
        return sector*pointSize + row;
    }
}


OBJMesh surfaceRev (vector<Vec3f> points, int sectors){

    OBJMesh m;
    auto &v = m.vertices;
    auto &t = m.triangles;

    for (auto point: points){
        v.push_back(point);
    }

    for (int sector = 1; sector <= sectors; sector++){

        float deltaPhi = (360.f/sectors)*sector;

        for (auto p:points){
            v.push_back(rotateAroundAxis(p,{0,1,0},deltaPhi));
        }

        for (int row = 0; row <points.size();row++){

            geometry::Indices a;
            a.vertexID() = getIndex(row,sector,points.size(),sectors);

            geometry::Indices b;
            b.vertexID() = getIndex(row, sector-1, points.size(), sectors);

            geometry::Indices c;
            c.vertexID() = getIndex(row+1, sector, points.size(), sectors);

            geometry::Indices d;
            d.vertexID() = getIndex(row+1, sector+1, points.size(), sectors);

            geometry::Triangle triA;



            t.push_back({ a,b,d });
            t.push_back({ a,d,c });

        }
    }

    return m;

}


void setupVAO(GLuint vaoID, GLuint vboID) {

	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	
	// set up position input into vertex shader
	glEnableVertexAttribArray(0);          // match layout # in shader
	glVertexAttribPointer(                 //
		0,                                 // attribute layout # (in shader)
		3,                                 // number of coordinates per vertex
		GL_FLOAT,                          // type
		GL_FALSE,                          // normalized?
		sizeof(Vec3f),                    // stride
		0									 // array buffer offset
	);

	glBindVertexArray(0);
}

GLFWwindow *initWindow() {
	GLFWwindow *window = nullptr;

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	std::cout << glfwVersion() << '\n';

	// set opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(1000,           // width
		1000,           // height
		"Mesh Loading", // title
		NULL,           // unused
		NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSwapInterval(1); // vsync
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);

	//Polygon fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// setup callbacks
	glfwSetFramebufferSizeCallback(window, setFrameBufferSize);
	glfwSetKeyCallback(window, setKeyboard);
    glfwSetMouseButtonCallback(window,setMouseButton);

	return window;
}

int main() {
	GLFWwindow *window = initWindow();

	auto vao_control = makeVertexArrayObject();
	auto vbo_control = makeBufferObject();
	auto vao_curve = makeVertexArrayObject();
	auto vbo_curve = makeBufferObject();

    auto vao_obj = makeVertexArrayObject();
    auto ibo_obj = makeBufferObject();
    auto vbo_obj = makeBufferObject();
    GLuint totalIndices = 0;

	Vec3f viewPosition(0, 0, 3);
	g_V = lookAtMatrix(viewPosition,    // eye position
		{ 0.f, 0.f, 0.f }, // look at
		{ 0.f, 1.f, 0.f }  // up vector
	);
	g_P = orthographicProjection(-1, 1, 1, -1, 0.001f, 10);

	
    auto basicShader = createShaderProgram("./shaders/basic_vs.glsl",
        "./shaders/basic_fs.glsl");
    auto phongShader = createShaderProgram("./shaders/phong_vs.glsl",
        "./shaders/phong_fs.glsl");


    assert(basicShader && phongShader);

	setupVAO(vao_control.id(), vbo_control.id());
	setupVAO(vao_curve.id(), vbo_curve.id());
    setupVAO(vao_obj.id(),vbo_obj.id());

	//Load control points
	std::vector<Vec3f> controlPoints;
	controlPoints.push_back({ 0,0.5,0 });
    controlPoints.push_back({ 1,0,0 });
    controlPoints.push_back({ 1,-0.5,0 });
    controlPoints.push_back({ 0,-1,0 });
	loadGeometryToGPU(controlPoints, vbo_control.id());
	
	//Load curve points
	std::vector<Vec3f> outCurve;
    outCurve = controlPoints;	//TODO - insert subdivision here
    outCurve = chaikinSubdiv(outCurve);
    outCurve = chaikinSubdiv(outCurve);

	loadGeometryToGPU(outCurve, vbo_curve.id());

    OBJMesh meshData = surfaceRev(outCurve,30);
    auto meshNormals = geometry::calculateVertexNormals(meshData.triangles,meshData.vertices);
    auto vboData = opengl::makeConsistentVertexNormalIndices(meshData,meshNormals);
    totalIndices = opengl::setup_vao_and_buffers(vao_obj,ibo_obj,vbo_obj,vboData);

		
	Vec3f color_curve(0, 1, 1);
	Vec3f color_control(1, 0, 0);
    
    Vec3f lightPos (0,1,0);

	//Set to one shader program 
	
	glPointSize(10);
	

	
	while (!glfwWindowShouldClose(window)) {

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        opengl::Program *phongProgram = &phongShader;

        phongProgram->use();
        vao_obj.bind();
        setUniformMat4f(phongProgram->uniformLocation("model"), g_M, true);
        setUniformMat4f(phongProgram->uniformLocation("view"), g_V, true);
        setUniformMat4f(phongProgram->uniformLocation("projection"), g_P, true);




        //setUniformVec3f(phongProgram->uniformLocation("lightPosition"),lightPos);
        //setUniformVec3f(phongShader.uniformLocation("lightPos"), lightPos);
        //setUniformVec3f(phongShader.uniformLocation("viewPos"), viewPosition);
        //setUniformVec3f(phongShader.uniformLocation("objectColor"), Vec3f(0.6,0.3,0));



        glViewport(0,0,g_width/2,g_height);
		


		glDrawElements(GL_TRIANGLES, totalIndices, GL_UNSIGNED_INT, (void*)0);
		


        opengl::Program *program = &basicShader;
        program->use();
        setUniformMat4f(program->uniformLocation("model"), g_M, true);
        setUniformMat4f(program->uniformLocation("view"), g_V, true);
        setUniformMat4f(program->uniformLocation("projection"), g_P, true);
        glViewport(g_width/2,0,g_width/2,g_height);
        setUniformVec3f(basicShader.uniformLocation("color"), color_curve);
        vao_curve.bind();
        glDrawArrays(GL_POINTS,   // type of drawing (rendered to back buffer)
            0,						  // offset into buffer
            outCurve.size()	// number of vertices in buffer
        );

        glDrawArrays(GL_LINE_STRIP,   // type of drawing (rendered to back buffer)
            0,						  // offset into buffer
            outCurve.size()	// number of vertices in buffer
        );
		//Draw control points
		setUniformVec3f(basicShader.uniformLocation("color"), color_control);
		vao_control.bind();
		glDrawArrays(GL_LINE_STRIP,   // type of drawing (rendered to back buffer)
			0,						  // offset into buffer
			controlPoints.size()	// number of vertices in buffer
		);

		glDrawArrays(GL_POINTS,   // type of drawing (rendered to back buffer)
			0,						  // offset into buffer
			controlPoints.size()	// number of vertices in buffer
		);


		glfwSwapBuffers(window); // swaps back buffer to front for drawing to screen
		glfwPollEvents();        // will process event queue and carry on
	}

	// cleaup window, and glfw before exit
	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
