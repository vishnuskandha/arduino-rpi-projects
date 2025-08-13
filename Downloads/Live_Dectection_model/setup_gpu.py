#!/usr/bin/env python3
"""
GPU Setup and Check for YOLOv13
"""

import torch
import subprocess
import sys

def check_gpu_availability():
    """Check GPU availability and CUDA support."""
    print("🔍 Checking GPU and CUDA availability...")
    print("=" * 50)
    
    # Check PyTorch CUDA support
    print(f"PyTorch version: {torch.__version__}")
    print(f"CUDA available: {torch.cuda.is_available()}")
    
    if torch.cuda.is_available():
        print(f"CUDA version: {torch.version.cuda}")
        print(f"GPU count: {torch.cuda.device_count()}")
        
        for i in range(torch.cuda.device_count()):
            print(f"GPU {i}: {torch.cuda.get_device_name(i)}")
            print(f"  Memory: {torch.cuda.get_device_properties(i).total_memory / 1024**3:.1f} GB")
        
        # Test GPU computation
        print("\n🧪 Testing GPU computation...")
        try:
            x = torch.randn(1000, 1000).cuda()
            y = torch.randn(1000, 1000).cuda()
            z = torch.mm(x, y)
            print("✅ GPU computation test passed!")
        except Exception as e:
            print(f"❌ GPU computation test failed: {e}")
    else:
        print("❌ CUDA not available")
        print("\n💡 To enable GPU support:")
        print("1. Install NVIDIA drivers")
        print("2. Install CUDA toolkit")
        print("3. Install PyTorch with CUDA support:")
        print("   pip install torch torchvision --index-url https://download.pytorch.org/whl/cu118")
    
    print("\n" + "=" * 50)

def install_cuda_pytorch():
    """Install CUDA-compatible PyTorch."""
    print("📦 Installing CUDA-compatible PyTorch...")
    
    try:
        # Uninstall current PyTorch
        subprocess.run([sys.executable, "-m", "pip", "uninstall", "torch", "torchvision", "-y"], 
                      check=True)
        print("✅ Uninstalled CPU PyTorch")
        
        # Install CUDA PyTorch
        subprocess.run([sys.executable, "-m", "pip", "install", "torch", "torchvision", 
                       "--index-url", "https://download.pytorch.org/whl/cu118"], 
                      check=True)
        print("✅ Installed CUDA PyTorch")
        
        # Verify installation
        import torch
        print(f"New PyTorch version: {torch.__version__}")
        print(f"CUDA available: {torch.cuda.is_available()}")
        
    except subprocess.CalledProcessError as e:
        print(f"❌ Error installing CUDA PyTorch: {e}")
    except Exception as e:
        print(f"❌ Unexpected error: {e}")

def main():
    print("🚀 YOLOv13 GPU Setup Utility")
    print("=" * 50)
    
    # Check current GPU status
    check_gpu_availability()
    
    # Ask user if they want to install CUDA PyTorch
    if not torch.cuda.is_available():
        response = input("\n❓ Do you want to install CUDA-compatible PyTorch? (y/n): ")
        if response.lower() == 'y':
            install_cuda_pytorch()
            print("\n🔄 Re-checking GPU availability...")
            check_gpu_availability()
    
    print("\n✅ GPU setup complete!")

if __name__ == "__main__":
    main()

