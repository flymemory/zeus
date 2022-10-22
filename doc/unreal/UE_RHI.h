// RHI（Render Hadware Interface）代表具体的API的平台硬件接口



FDynamicRHIModule
{
private:
    TArray<TSharePtr<FAdapter>> ChosenAdapters;

    // Enumrates all adapters, pick the most suitable one.
    void FindAdapter();

public:
    FDynamicRHI* CreateRHI(FeatureLevel);
}


class FDynamicRHI
{
protected:
    TArray<TSharePtr<FAdapter>> ChosenAdapters;

public:
    FAdapter& GetAdapter(int Index);
    int GetNumAdapters() const;

    FDevice* GetRHIDevice(uint32 6GPUIndex);

public: 
    template <typename TRHIType>
        static typename *ResourceCast();

    void CreateCommandQueue();

    RHICreateSamplerState();
    RHICreateRasterizerState();
    RHICreateDepthStencilState();
    RHICreateBlendState();
    RHICreateVertexDeclaration();
    RHICreatePixelShader();
    RHICreateVertexShader();
    RHICreateGUPFence();
    RHICreateStagingBuffer();
    RHICreateTransition();
    RHIReleaseTransition();

    void TransitionResource(CommandList, View, After);
}