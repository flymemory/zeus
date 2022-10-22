
class FDevice
{
public:
    inline FD3D12OfflineDescriptorManager& GetSamplerDescriptorAllocator() { return SamplerAllocator; }
	inline FD3D12CommandListManager& GetCommandListManager() { return *CommandListManager; }
	inline FD3D12CommandListManager& GetCopyCommandListManager() { return *CopyCommandListManager; }
	inline FD3D12CommandListManager& GetAsyncCommandListManager() { return *AsyncCommandListManager; }
	inline FD3D12CommandAllocatorManager& GetTextureStreamingCommandAllocatorManager() { return TextureStreamingCommandAllocatorManager; }
    inline FDefaultBufferAllocator* GetDefaultBufferAlolocator();

protected:
    FCommandListManager* CommandListManager;
    FCommandListManager* CopyCommandListManager;
    FCommandListManager* AsyncCommandListManager;

    // A pool of command allocators that texture streaming threads share
    FCommandAllocatorManager* TextureStreamingCommandAllocatorManager;

    FGlobalHeap GlobalViewHeap;
}

class FRHICommandList
{
    /** A mask where each bit is a GPU index. Can not be empty so that non SLI platforms can optimize it to be always 1.  */
    FRHIGPUMask GPUMask;

public:
    void Flush();

    FVertexShaderRHIRef CreateVertexShader();
    FPixelShaderRHIRef CreatePixelShader();
    FComputeShaderRHIRef CreateComputeShader();

    FGPUFenceRHIRef CreateComputeFence();
}

class FRHICommandContext
{
public:
    void RHIBeginDrawingViewport();
    void RHIEndDrawingViewport();

    void RHIBeginFrame();
    void RHIEndFrame();

    // Obtain a new command list from command list manager.
    void OpenCommandList();
    void CloseCommandList();


public:
    // Refresh the state cache.
    void RHISetShaderTexture();
    void RHISetShaderUniformBuffer();


    // Aplly the state cache, and submit the command to command list of device, conditional refresh command list.
    void RHIDrawPrimitive();
}

class FCommandContext : public FRHICommandContext
{
    
} 




class FDefaultBufferAllocator
{
    FDefualtBufferPool* CreateBufferPool()
    {
        // Create a allocator, BuddyAllocator, BucketAllocator, MultiBuddyAllocator
    }
}

class FResourceAllocator
{


}

// Resources are allocated from buckets, which are just a collection of resources of a particular size.
class FBucketAllocator : public FResourceAllocator
{
public:
    void Allocate(uint32 SizeInBytes, uint32 Alignment, FResourceLocation& ResourceLocation)
    {
        // Find free position, otherwise create one.

    }

protected:
    static const uint32 BucketShift = 6;
	static const uint32 NumBuckets = 22; // bucket resource sizes range from 64 to 2^28 

    FThreadSafeQueue<FBlockAllocatorPrivateData> AvailableBlocks[NumBuckets];
    FThreadSafeQueue<FBlockAllocatorPrivateData> ExpiredBlocks;
    TArray<FResource*> SubAllocatedResources;
}

// Allocates blocks from a fixed range using buddy allocation method.
// Buddy allocation allows reasonably fast allocation of arbitrary size blocks
// with minimal fragmentation and provides efficient reuse of freed ranges.
// When a block is de-allocated an attempt is made to merge it with it's 
// neighbour (buddy) if it is contiguous and free.
// Based on reference implementation by MSFT: billkris

// Unfortunately the api restricts the minimum size of a placed buffer resource to 64k
#define MIN_PLACED_BUFFER_SIZE (64 * 1024)
#define D3D_BUFFER_ALIGNMENT (64 * 1024)

class FBuddyAllocator : public FResourceAllocator
{
public:
    void Allocate(uint32 SizeInBytes, uint32 Alignment, FResourceLocation& ResourceLocation)
    {
        // Allocate the resource on BackingResource that we pre-allocate

    }
protected:
	const uint32 MaxBlockSize;
	const uint32 MinBlockSize;
	const FD3D12BuddyAllocator::EAllocationStrategy AllocationStrategy;

	TRefCountPtr<FD3D12Resource> BackingResource;
	TRefCountPtr<FD3D12Heap> BackingHeap;
}


//-----------------------------------------------------------------------------
//	Multi-Buddy Allocator
//-----------------------------------------------------------------------------
// Builds on top of the Buddy Allocator but covers some of it's deficiencies by
// managing multiple buddy allocator instances to better match memory usage over
// time.

class FD3D12MultiBuddyAllocator : public FD3D12ResourceAllocator
{

public:
    bool TryAllocate(uint32 SizeInBytes, uint32 Alignment, FD3D12ResourceLocation& ResourceLocation)
    {
        FScopeLock Lock(&CS);

        for (int32 i = 0; i < Allocators.Num(); i++)
        {
            if (Allocators[i]->TryAllocate(SizeInBytes, Alignment, ResourceLocation))
            {
                return true;
            }
        }

        Allocators.Add(CreateNewAllocator(SizeInBytes));
        return Allocators.Last()->TryAllocate(SizeInBytes, Alignment, ResourceLocation);
    }

protected:
	const FD3D12BuddyAllocator::EAllocationStrategy AllocationStrategy;
	const uint32 MinBlockSize;
	const uint32 DefaultPoolSize;

	TArray<FD3D12BuddyAllocator*> Allocators; 
}