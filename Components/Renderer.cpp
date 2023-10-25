#include "Renderer.h"


void IRenderer::SetFlag(FLAGS _flag)
{
    flags |= _flag; // bitwise OR
}

void IRenderer::RemoveFlag(FLAGS _flag)
{
    flags &= ~_flag; //bitwise AND and bitwise NOT
}

bool IRenderer::IsFlagSet(FLAGS _flag)
{
    return (flags & _flag) != 0;
}