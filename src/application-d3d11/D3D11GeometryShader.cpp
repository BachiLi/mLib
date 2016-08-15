
void ml::D3D11GeometryShader::load(
	GraphicsDevice& g, 
	const std::string& filename, 
	const std::string& entryPoint, 
	const std::string& shaderModel,
	const std::vector<std::pair<std::string, std::string>>& shaderMacros)
{
    m_graphics = &g.castD3D11();

	release();
	SAFE_RELEASE(m_blob);

	m_filename = filename;
	g.castD3D11().registerAsset(this);

	m_blob = D3D11Utility::CompileShader(m_filename, entryPoint, shaderModel, shaderMacros);
	MLIB_ASSERT_STR(m_blob != nullptr, "CompileShader failed");

	reset();
}

void ml::D3D11GeometryShader::release()
{
	SAFE_RELEASE(m_shader);
}

void ml::D3D11GeometryShader::reset()
{
	release();

	auto &device = m_graphics->getDevice();

	D3D_VALIDATE(device.CreateGeometryShader(m_blob->GetBufferPointer(), m_blob->GetBufferSize(), nullptr, &m_shader));
}

void ml::D3D11GeometryShader::bind() const
{
	m_graphics->getContext().GSSetShader(m_shader, nullptr, 0);
}