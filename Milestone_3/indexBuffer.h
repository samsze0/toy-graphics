class IndexBuffer {
private:
  unsigned int ID;
public:
  IndexBuffer(const void* indices, unsigned int count);
  ~IndexBuffer();
  void Bind() const;
  void Unbind() const;
};