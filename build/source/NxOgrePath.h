/** 
    
    This file is part of NxOgre.
    
    Copyright (c) 2009 Robin Southern, http://www.nxogre.org
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
    
*/

                                                                                       

#ifndef NXOGRE_PATH_H
#define NXOGRE_PATH_H

#include "NxOgreStable.h"
#include "NxOgreString.h"

                                                                                       

namespace NxOgre
{

                                                                                       

/* \brief Simple path class used with ResourceSystem to represent paths in a filesystem, or represent identifiers to
          resources in archives using a specific protocol.
          
          A path is formatted as;
          
            protocol://drive:/directory_name/sub_directory_name/filename.extension#portion
            
            
   \examples
          
          file://C:/Program Files/Game/Game.exe               (Specific file)
          
          file://C:/Program Files/Game/                       (Directory)
          
          file://../Game/                                     (Relative Directory with ".." operator)
            Resolves to: file://..Game/

          file://C:/Program Files/Game/../OtherGame/Game.exe  (Directory ".." resolving)
            Resolves to:  file://C:/Program Files/OtherGame/Game.exe

          file://Game.exe                                     (Relative File)
          
          zip://C:/Program Files/Game/media.zip               (Example Zip Resource Protocol)
          
          zip://C:/Program Files/Game/media.zip#file.nxs      (Access file.nxs in media.zip)
          
          zip://media.zip#file.nxs                            (Relative file, accessing a file in file.nxs zip file)
          
          file:///home/franky/Desktop/file.nxs                (Supports Linux paths)
          
          memory://                                           (Protocol is given only)
          
          
   \usage
     <code>
       
       1. Basic usage
        Path path("c:/Program Files/My Game/Game.exe");
       
       2. ".." modifiers work.
        Path path("c:/Program Files/My Game/../No my other game/Game.exe");
       
       3. Combining two paths together with the / operator.
        Path path = Path("c:/Program Files/My Game/../No my other game/) / Path("Game.exe");
       
       4. Combining a path and string together with the / operator.
        Path path = Path("c:/Program Files/My Game/../No my other game/) / "Game.exe";
       
       5. Multi-line combination of paths.
        Path path("c:/Program Files/");
        path /= "My Game/";
        path /= "Game.exe";
       
       6. Getting the parent path.
        Path path("c:/Program Files/My Game");
        Path program_files = path.getParent().getParent();
        program_files /= "My Other Game/OtherGame.exe";
       
       7. Getting the filename of the path
        Path path("c:/Program Files/My Game/Game.exe");
        path.getFilename() => Game.exe
       
       8. Getting the directory name of the file.
        Path path("c:/Program Files/My Game/Game.exe");
        path.getDirectory() => My Game
       
       9. Getting the parent directory name of the file.
        Path path("c:/Program Files/My Game/Game.exe");
        path.getDirectory(1) => Program Files
       
      10. Using protocols and portions.
        Path path("zip://c:/Program Files/My Game/media.zip#poem.txt");
        path.getProtocol() => zip
        path.getPortion() => poem.txt
      
      11. Natural protocols
        Path path("file://c:/Program Files/My Game/Game.exe");
        path.getProtocol() => file
        Path path("c:/Program Files/My Game/Game.exe");
        path.getProtocol() => file
     </code>
*/
class NxOgrePublicClass Path
{
   
 public:
   
   static const Path BAD_PATH;
   
   Path();
   
   Path(const char* path);
   
   Path(const String& path);
   
   Path(const Path&);
   
  ~Path();
   
   Path& operator=(const Path&);
   
   Path operator /(const Path& other);
   
   Path operator /(const String& other);
   
   Path operator /(const char* other);
   
   Path& operator /=(const Path& other);
   
   Path& operator /=(const String& other);
   
   Path& operator /=(const char* other);
   
   /** \brief Get the directory of the path, or the directories of lower levels.
   */
   String getDirectory(unsigned int parent_level = 0) const;
      
   /** \brief Get the number of directories or how deep the file is.
   */
   unsigned int getNbDirectories() const;
   
   /** \brief Get the filename (and extension)
   */
   String getFilename() const;
   
   /** \brief Has the path have a filename?
   */
   bool hasFilename() const;

   /** \brief Get just the filename (no extension)
   */
   String getFilenameOnly() const;
   
   /** \brief Get the extension
   */
   String getExtension() const;
   
   /** \brief Has an extension?
   */
   bool hasExtension() const;
   
   /** \brief Get the portion
   */
   String getPortion() const;
   
   /** \brief Has an extension?
   */
   bool hasPortion() const;
   
   /** \brief Get the protocol
   */
   String getProtocol() const;
   
   /** \brief Get the hash of the protocol
   */
   StringHash getProtocolHash() const;
   
#if NxOgrePlatform == NxOgrePlatformWindows
   /** \brief Get the drive.
   */
   String getDrive() const;
#endif

#if NxOgrePlatform == NxOgrePlatformWindows
   /** \brief Has an extension?
   */
   bool hasDrive() const;
#endif

   /** \brief Is the path absolute or relative?
   */
   bool isAbsolute() const;
   
   /** \brief Get parent path. A directory (if has filename), drive (has one directory and no filename) or file (has portion).
   */
   Path getParent() const;

   /** \brief Get relative path to the file, the path without directories or drives.
   */
   Path getRelative() const;
   
   /** \brief Correctly format it.
   */
   String getString() const;
   
   /** \brief Correctly format it as a OS string; no protocol or portion.
   */
   String getOSString();
   
   /*! function. dump
       desc.
           Developer/Testing function.
   */
   std::string dump() const;

 protected:
   
   /** \internal Turns path into drive, filename, directories, etc.
   */
   void set(const String& path);
   
   /** \internal Clears the path.
   */
   void clear();

   String            mProtocol,
#if NxOgrePlatform == NxOgrePlatformWindows
                     mDrive,
#endif
                     mFilename,
                     mExtension,
                     mPortion;
   
   std::list<String> mDirectories;
   
   bool              mAbsolute;
   
};


                                                                                       

} // namespace NxOgre

                                                                                       

#endif
