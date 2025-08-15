# scripts/sami_ttt/behavior_runner.py
from pathlib import Path
import os, sys, threading

# Figure out project paths
scripts_dir  = Path(__file__).resolve().parents[1]   # .../scripts
repo_root    = scripts_dir.parent                    # repo root
software_dir = repo_root / "software"
behaviors_dir = software_dir / "behaviors"
audio_dir     = software_dir / "audio"

# Make sure Python can import modules from software/
if str(software_dir) not in sys.path:
    sys.path.insert(0, str(software_dir))

from SAMIControl import SAMIControl   # now this works

# Singleton controller (reuse one serial connection)
_controller = None
_lock = threading.Lock()

def _get_controller():
    global _controller
    if _controller:
        return _controller
    with _lock:
        if _controller:
            return _controller

        port = os.environ.get("SAMI_PORT", "/dev/tty.usbserial-130")
        baud = int(os.environ.get("SAMI_BAUD", "115200"))

        ctrl = SAMIControl(
            arduino_port=port,
            baud_rate=baud,
            joint_config_file=str(software_dir / "Joint_config.json"),
            behavior_folder=str(behaviors_dir),
            emote_file=str(software_dir / "Emote.json"),
            audio_folder=str(audio_dir),
            starting_voice="Matt",
        )
        ctrl.initialize_serial_connection()
        _controller = ctrl
        return _controller

def run_behavior(name_or_filename: str):
    """Call: run_behavior('SadShrimp') or run_behavior('SadShrimp.json')"""
    ctrl = _get_controller()
    fname = name_or_filename if name_or_filename.endswith(".json") else f"{name_or_filename}.json"
    ctrl.start_behavior(fname)
