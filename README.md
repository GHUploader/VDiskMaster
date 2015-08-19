# VDiskMaster
Software for managing and creating virtual disks.

The design plan:
  - to keep file managing, driver IO, and formatting logic in dll files
  - implement a console interface
  - implement a Win32 GUI
  
The purpose of the project:

  To simplify OS development by allowing the developer to inject boot code with a certain size ( < 510 bytes, as there should be room for BPB block, etc.)
into the MBR, and to create a file system with a certain format to allow for file storage.
