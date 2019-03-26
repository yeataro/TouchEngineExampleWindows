#include "stdafx.h"
#include "OpenGLProgram.h"


OpenGLProgram::OpenGLProgram()
{
}


OpenGLProgram::~OpenGLProgram()
{
}

bool OpenGLProgram::build(const char * vs, const char * fs)
{
    destroy();

    GLuint frag = compileShader(fs, GL_FRAGMENT_SHADER);
    GLuint vert = compileShader(vs, GL_VERTEX_SHADER);

    if (frag && vert)
    {
        myProgram = glCreateProgram();
        glAttachShader(myProgram, frag);
        glAttachShader(myProgram, vert);
    }

    if (frag)
    {
        glDeleteShader(frag);
    }
    if (vert)
    {
        glDeleteShader(vert);
    }

    if (myProgram)
    {
        GLint status;

        glLinkProgram(myProgram);
        glGetProgramiv(myProgram, GL_LINK_STATUS, &status);
        if (status == GL_FALSE)
        {
            glDeleteProgram(myProgram);
            myProgram = 0;
        }
    }
    if (myProgram)
    {
        return true;
    }
    return false;
}

void OpenGLProgram::destroy()
{
    if (myProgram != 0)
    {
        glDeleteProgram(myProgram);
        myProgram = 0;
    }
}

GLuint OpenGLProgram::compileShader(const char * source, GLenum type)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        glDeleteShader(shader);
        shader = 0;
    }

    return shader;
}
