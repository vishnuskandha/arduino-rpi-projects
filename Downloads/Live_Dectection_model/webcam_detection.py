#!/usr/bin/env python3
"""
Webcam Object Detection with YOLOv13
Supports both GPU and CPU inference
"""

from ultralytics import YOLO
import torch
import cv2
import time
import argparse
import numpy as np

class WebcamDetector:
    def __init__(self, model_path='yolov13n.pt', device='auto', conf_threshold=0.5):
        """
        Initialize the webcam detector.
        
        Args:
            model_path (str): Path to the YOLO model
            device (str): 'auto', 'cpu', or 'cuda'
            conf_threshold (float): Confidence threshold for detections
        """
        self.model_path = model_path
        self.conf_threshold = conf_threshold
        self.device = self._setup_device(device)
        self.model = self._load_model()
        
    def _setup_device(self, device):
        """Setup the device for inference."""
        if device == 'auto':
            if torch.cuda.is_available():
                device = 'cuda'
                print(f"🚀 Using GPU: {torch.cuda.get_device_name()}")
            else:
                device = 'cpu'
                print("🖥️  Using CPU for inference")
        elif device == 'cuda' and not torch.cuda.is_available():
            print("⚠️  CUDA not available, falling back to CPU")
            device = 'cpu'
        
        return device
    
    def _load_model(self):
        """Load the YOLO model."""
        print(f"📥 Loading model: {self.model_path}")
        try:
            model = YOLO(self.model_path)
            print(f"✅ Model loaded successfully on {self.device}")
            return model
        except Exception as e:
            print(f"❌ Error loading model: {e}")
            return None
    
    def start_webcam(self, camera_id=0, show_fps=True, save_video=False, output_path='output.mp4'):
        """
        Start webcam detection.
        
        Args:
            camera_id (int): Camera device ID (usually 0 for default webcam)
            show_fps (bool): Whether to display FPS
            save_video (bool): Whether to save the video
            output_path (str): Output video file path
        """
        if self.model is None:
            print("❌ Model not loaded. Cannot start webcam detection.")
            return
        
        # Initialize video capture
        cap = cv2.VideoCapture(camera_id)
        if not cap.isOpened():
            print(f"❌ Error: Could not open camera {camera_id}")
            return
        
        # Get camera properties
        width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
        height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
        fps = cap.get(cv2.CAP_PROP_FPS)
        
        print(f"📹 Camera initialized: {width}x{height} @ {fps:.1f} FPS")
        
        # Initialize video writer if saving
        video_writer = None
        if save_video:
            fourcc = cv2.VideoWriter_fourcc(*'mp4v')
            video_writer = cv2.VideoWriter(output_path, fourcc, fps, (width, height))
            print(f"💾 Video will be saved to: {output_path}")
        
        # Performance tracking
        frame_count = 0
        start_time = time.time()
        fps_list = []
        
        print("\n🎥 Starting webcam detection...")
        print("Press 'q' to quit, 's' to save screenshot, 'h' to show/hide FPS")
        
        try:
            while True:
                # Read frame
                ret, frame = cap.read()
                if not ret:
                    print("❌ Error reading frame")
                    break
                
                # Run detection
                frame_start = time.time()
                results = self.model(frame, conf=self.conf_threshold, verbose=False)
                inference_time = time.time() - frame_start
                
                # Calculate FPS
                frame_count += 1
                current_fps = 1.0 / inference_time
                fps_list.append(current_fps)
                if len(fps_list) > 30:  # Keep last 30 frames for average
                    fps_list.pop(0)
                avg_fps = sum(fps_list) / len(fps_list)
                
                # Draw detections
                annotated_frame = results[0].plot()
                
                # Add performance info
                if show_fps:
                    # Add FPS and device info
                    cv2.putText(annotated_frame, f"FPS: {avg_fps:.1f}", 
                               (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
                    cv2.putText(annotated_frame, f"Device: {self.device.upper()}", 
                               (10, 70), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
                    cv2.putText(annotated_frame, f"Inference: {inference_time*1000:.1f}ms", 
                               (10, 110), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
                    
                    # Add detection count
                    num_detections = len(results[0].boxes) if results[0].boxes is not None else 0
                    cv2.putText(annotated_frame, f"Detections: {num_detections}", 
                               (10, 150), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
                
                # Save video frame
                if save_video and video_writer:
                    video_writer.write(annotated_frame)
                
                # Display frame
                cv2.imshow('YOLOv13 Webcam Detection', annotated_frame)
                
                # Handle key presses
                key = cv2.waitKey(1) & 0xFF
                if key == ord('q'):
                    print("👋 Quitting...")
                    break
                elif key == ord('s'):
                    # Save screenshot
                    timestamp = time.strftime("%Y%m%d_%H%M%S")
                    screenshot_path = f"screenshot_{timestamp}.jpg"
                    cv2.imwrite(screenshot_path, annotated_frame)
                    print(f"📸 Screenshot saved: {screenshot_path}")
                elif key == ord('h'):
                    show_fps = not show_fps
                    print(f"📊 FPS display: {'ON' if show_fps else 'OFF'}")
                
        except KeyboardInterrupt:
            print("\n👋 Interrupted by user")
        
        finally:
            # Cleanup
            cap.release()
            if video_writer:
                video_writer.release()
            cv2.destroyAllWindows()
            
            # Print final statistics
            total_time = time.time() - start_time
            print(f"\n📊 Final Statistics:")
            print(f"   Total frames processed: {frame_count}")
            print(f"   Total time: {total_time:.2f} seconds")
            print(f"   Average FPS: {frame_count/total_time:.2f}")
            if fps_list:
                print(f"   Peak FPS: {max(fps_list):.2f}")
                print(f"   Average inference time: {1000/avg_fps:.1f}ms")

def main():
    parser = argparse.ArgumentParser(description='YOLOv13 Webcam Detection')
    parser.add_argument('--model', type=str, default='yolov13n.pt', 
                       help='Path to YOLO model (default: yolov13n.pt)')
    parser.add_argument('--device', type=str, default='auto', 
                       choices=['auto', 'cpu', 'cuda'], 
                       help='Device to use for inference (default: auto)')
    parser.add_argument('--camera', type=int, default=0, 
                       help='Camera device ID (default: 0)')
    parser.add_argument('--conf', type=float, default=0.5, 
                       help='Confidence threshold (default: 0.5)')
    parser.add_argument('--save', action='store_true', 
                       help='Save video to file')
    parser.add_argument('--output', type=str, default='output.mp4', 
                       help='Output video file path (default: output.mp4)')
    parser.add_argument('--no-fps', action='store_true', 
                       help='Hide FPS display')
    
    args = parser.parse_args()
    
    # Create detector
    detector = WebcamDetector(
        model_path=args.model,
        device=args.device,
        conf_threshold=args.conf
    )
    
    # Start webcam detection
    detector.start_webcam(
        camera_id=args.camera,
        show_fps=not args.no_fps,
        save_video=args.save,
        output_path=args.output
    )

if __name__ == "__main__":
    main()

