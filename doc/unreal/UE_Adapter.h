

class FAdapter
{
private:
    TRefCountPtr<ID3D12Device> RootDevice;
    // CreatePipelineLibrary
    TRefCountPtr<ID3D12Device1> RootDevice1;
    TRefCountPtr<ID3D12Device2> RootDevice2;

    TRefCountPtr<ID3D12Device5> RootDevice5;

public:
    FAdapter();
    ~FAdapter();

    void Initialize() {
        __CreateRootDevice();
    }

    // Initialize all devices.
    void InitializeDevices();


    void __CreateRootDevice() {
        // Create root device.

    }

    template<class BufferType>
    BufferType* CreateRHIBuffer()
    {
        BufferType* BufferOut = new BufferType();

        AllocateBuffer(BufferOut);

        return BufferOut;
    }
    void AllocateBuffer(FDevice *Device, DESC， uint32 Size, uint32 InUsage, uint32 Alignment);
};