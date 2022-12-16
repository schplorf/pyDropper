# pyDropper
Embed executables in a python file to drop and execute


Just dumps a giant base64 string into a .py script lol

## How to use
Simply drop the header into your source code, then you can use `generatePyDropper(path)` where `path` is some executable on disk to create an std::string containing dropper code.


Example:
```
int main(){
  std::string pyDropperCode = generatePyDropper("C:\\Users\\user\\Desktop\\test.exe");
  std::ofstream outFile("C:\\Users\\user\\Desktop\\testDropper.py");
  outFile << pyDropperCode;
  outFile.close();
  return 0;
}
```
