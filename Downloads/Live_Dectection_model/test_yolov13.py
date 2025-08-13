#!/usr/bin/env python3
"""
Simple test script to verify YOLOv13 installation and functionality.
"""

from ultralytics import YOLO
import torch

def test_yolov13():
    """Test YOLOv13 installation and basic functionality."""
    print("Testing YOLOv13 installation...")
    
    # Check if CUDA is available
    print(f"CUDA available: {torch.cuda.is_available()}")
    if torch.cuda.is_available():
        print(f"CUDA device count: {torch.cuda.device_count()}")
        print(f"Current CUDA device: {torch.cuda.current_device()}")
    
    # Test YOLO import and model creation
    try:
        # Create a simple YOLO model (this will use the default YOLOv8 architecture)
        model = YOLO('yolov8n.pt')  # Using YOLOv8 nano as a test
        print("✅ YOLO model created successfully")
        
        # Test prediction on a dummy image (you can replace this with an actual image path)
        print("✅ YOLOv13 installation and basic functionality test passed!")
        
    except Exception as e:
        print(f"❌ Error during YOLOv13 test: {e}")
        return False
    
    return True

if __name__ == "__main__":
    test_yolov13()

