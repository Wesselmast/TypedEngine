#pragma once


class VertexBuffer {
public:
	virtual ~VertexBuffer() = default;

	void setLayout(unsigned int* layout, unsigned int layoutSize) {
		this->layout = layout;
		this->layoutSize = layoutSize;
	}

	inline unsigned int* getLayout() const { 
		return layout; 
	}

	inline unsigned int getLayoutSize() const {
		return layoutSize;
	}

	virtual void bind() = 0;
	virtual void unbind() = 0;

protected:
	unsigned int* layout;
	unsigned int  layoutSize;
	unsigned int  rendererID;

};