class VertexBuffer {
private:
  unsigned int ID;
public:
  VertexBuffer(const void* vertexData, unsigned int size);
  ~VertexBuffer();
  void Bind() const;
  void Unbind() const;
};