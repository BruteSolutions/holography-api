#ifndef PROJECTOR_H_
#define PROJECTOR_H_

class Projector
{
public:
  Projector(); //TODO: dummy
  unsigned int getBufferSize();
  ColorTranslator getColorTranslator();
  void setConfiguration(Configuration c);
  Configuration getConfiguration();
  void highlight();
  void unHighlight();
  int* getBuffer();
  void display(Scene scn);
  void addShader(Shader s);
private:
  std::list<Shader> shaders; 
};

#endif
