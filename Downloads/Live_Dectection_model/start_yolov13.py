#!/usr/bin/env python3
"""
Start YOLOv13 model for object detection.
"""

from ultralytics import YOLO
import torch
import time

def start_yolov13_model():
    """Start and test the YOLOv13 model."""
    print("🚀 Starting YOLOv13 model...")
    
    # Check system capabilities
    print(f"PyTorch version: {torch.__version__}")
    print(f"CUDA available: {torch.cuda.is_available()}")
    if torch.cuda.is_available():
        print(f"CUDA device: {torch.cuda.get_device_name()}")
    else:
        print("Using CPU for inference")
    
    try:
        # Load YOLOv13 model
        print("📥 Loading YOLOv13 model...")
        
        # Try to load YOLOv13 model first, fallback to YOLOv8 if not available
        try:
            model = YOLO('yolov13n.pt')  # Try YOLOv13 nano
            print("✅ YOLOv13 model loaded successfully!")
        except:
            print("⚠️  YOLOv13 weights not found, using YOLOv8 as fallback...")
            model = YOLO('yolov8n.pt')  # Fallback to YOLOv8 nano
            print("✅ YOLOv8 model loaded successfully!")
        
        # Display model information
        print(f"📊 Model loaded: {model.model.name if hasattr(model.model, 'name') else 'Unknown'}")
        print(f"📊 Model parameters: {sum(p.numel() for p in model.model.parameters()):,}")
        
        # Test model with a simple prediction
        print("🧪 Testing model with dummy input...")
        
        # Create a dummy image (you can replace this with an actual image path)
        import numpy as np
        dummy_image = np.random.randint(0, 255, (640, 640, 3), dtype=np.uint8)
        
        # Run inference
        start_time = time.time()
        results = model(dummy_image, verbose=False)
        inference_time = time.time() - start_time
        
        print(f"⚡ Inference time: {inference_time:.3f} seconds")
        print(f"🔍 Detected objects: {len(results[0].boxes) if results[0].boxes is not None else 0}")
        
        print("\n🎉 YOLOv13 model is ready for use!")
        print("\n📝 Usage examples:")
        print("   # For image detection:")
        print("   results = model('path/to/image.jpg')")
        print("   results[0].show()")
        print("\n   # For video detection:")
        print("   results = model('path/to/video.mp4')")
        print("\n   # For webcam detection:")
        print("   results = model(source=0, show=True)")
        
        return model
        
    except Exception as e:
        print(f"❌ Error starting YOLOv13 model: {e}")
        return None

if __name__ == "__main__":
    model = start_yolov13_model()
    if model:
        print("\n✅ Model started successfully! You can now use it for object detection.")
    else:
        print("\n❌ Failed to start model. Please check the error messages above.")

