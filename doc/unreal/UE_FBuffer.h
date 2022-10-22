class FBuffer
{

}

class FIndexBufer : public FRHIIndexBuffer, public FBuffer
{

}

class FVertexBuffer : public FRHIVertexBuffer, public FBuffer
{

}

class FStructuredBuffer : public FRHIStructuredBuffer, public FBuffer
{

}

class FUniformBuffer : public FRHIUniformBuffer
{
    
}