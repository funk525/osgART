/* -*-c++-*- 
 * 
 * osgART - ARToolKit for OpenSceneGraph
 * Copyright (C) 2005-2009 Human Interface Technology Laboratory New Zealand
 * 
 * This file is part of osgART 2.0
 *
 * osgART 2.0 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * osgART 2.0 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with osgART 2.0.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "osgART/GeometryUtils"

namespace osgART {


void addTexturedQuad(osgART::VideoGeode& geode, float width, float height)
{

	float maxU(1.0);
	float maxV(1.0);
	
/*	if (geode.getTextureMode() == osgART::VideoGeode::USE_TEXTURE_RECTANGLE) 
	{
		maxU = width;
		maxV = height;
	} else 
	{
		maxU = width / (float)osgART::nextPowerOfTwo((unsigned int)width);
		maxV = height / (float)osgART::nextPowerOfTwo((unsigned int)height);
	}*/
	
	osg::Geometry* geometry = new osg::Geometry();
		
	osg::Vec3Array* vcoords = new osg::Vec3Array();
	geometry->setVertexArray(vcoords);

	osg::Vec2Array* tcoords = new osg::Vec2Array();
	geometry->setTexCoordArray(0, tcoords);

	vcoords->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	vcoords->push_back(osg::Vec3(width, 0.0f, 0.0f));
	vcoords->push_back(osg::Vec3(width, height, 0.0f));
	vcoords->push_back(osg::Vec3(0.0f,  height, 0.0f));

	tcoords->push_back(osg::Vec2(0.0f, maxV));
	tcoords->push_back(osg::Vec2(maxU, maxV));
	tcoords->push_back(osg::Vec2(maxU, 0.0f));
	tcoords->push_back(osg::Vec2(0.0f, 0.0f));

	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	geode.addDrawable(geometry);
}

/** 
 * Creates and returns an osg::Geode containing a simple box of the specified size.
 * \param	size	The edge length of the cube. Default value is 80mm.
 * \param	color	The color of the cube. Default value is white.
 * \return	The osg::Geode containing the cube shape.
 */
osg::Geode* testCube(float size, osg::Vec4 color) {
	osg::Geode* geode = new osg::Geode();
	osg::ShapeDrawable* sd = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0, 0, size / 2.0f), size));
	sd->setColor(color);
	geode->addDrawable(sd);
	return geode;
}

osg::Node* loadModel(std::string filename) {

	osg::Node* model=osgDB::readNodeFile(filename);

	if (model!=NULL)
	{
		return model;
	}
	else
	{
		osg::notify(osg::FATAL) << "Could not load model:" <<filename<<std::endl;
		exit(-1);
	}
}

osg::MatrixTransform* scaleModel(osg::Node* model, float scalefactor) {
	osg::MatrixTransform* scaleTransfo;

	scaleTransfo=new osg::MatrixTransform(osg::Matrix::scale(scalefactor,scalefactor,scalefactor));
	scaleTransfo->addChild(model);

	return scaleTransfo;
}

osg::MatrixTransform* translateUpModel(osg::Node* model, float z) {
	osg::MatrixTransform* translateUpTransfo;

	translateUpTransfo=new osg::MatrixTransform(osg::Matrix::translate(0.,0.,z));
	translateUpTransfo->addChild(model);

	return translateUpTransfo;
}


};//namespace osgART
