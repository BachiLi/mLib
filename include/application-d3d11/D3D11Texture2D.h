
#ifndef APPLICATION_D3D11_D3D11TEXTURE2D_H_
#define APPLICATION_D3D11_D3D11TEXTURE2D_H_

namespace ml {

//TODO templetize based on type
class D3D11Texture2D : public GraphicsAsset
{
public:
    D3D11Texture2D()
	{
        m_graphics = nullptr;
        m_texture = nullptr;
        m_srv = nullptr;
	}

	D3D11Texture2D(const D3D11Texture2D& t)
	{
		m_graphics = nullptr;
		m_texture = nullptr;
		m_srv = nullptr;
		if (t.isLoaded()) {
			load(*t.m_graphics, t.getImage());
		}
	}

    D3D11Texture2D(D3D11Texture2D &&t)
    {
        m_image = std::move(t.m_image);
        m_graphics = t.m_graphics;
        m_srv = t.m_srv; t.m_srv = nullptr;
        m_texture = t.m_texture; t.m_texture = nullptr;
    }

    void operator= (D3D11Texture2D &&t)
    { 
        m_image = std::move(t.m_image);
        m_graphics = t.m_graphics;
        m_srv = t.m_srv; t.m_srv = nullptr;
        m_texture = t.m_texture; t.m_texture = nullptr;
    }

    ~D3D11Texture2D()
	{
		release();
	}

	D3D11Texture2D(GraphicsDevice &g, const ColorImageR8G8B8A8& image)
    {
        m_texture = nullptr;
        m_srv = nullptr;
        load(g, image);
    }
    void load(GraphicsDevice &g, const ColorImageR8G8B8A8 &image);

	void release();
	void reset();

	void bind(unsigned int slot = 0) const;
	void unbind(unsigned int slot = 0) const;

	const ColorImageR8G8B8A8& getImage() const   {
        return m_image;
    }

	bool isLoaded() const {
		return m_texture != nullptr;
	}

private:
	D3D11GraphicsDevice *m_graphics;
	ColorImageR8G8B8A8 m_image;
    ID3D11Texture2D *m_texture;
    ID3D11ShaderResourceView *m_srv;
};

}  // namespace ml

#endif  // APPLICATION_D3D11_D3D11TEXTURE2D_H_
