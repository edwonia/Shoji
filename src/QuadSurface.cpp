#include "QuadSurface.h"

void QuadSurface::update( ofxCvContourFinder & a_contour )
{
	// ignore if not 4 points
	if ( a_contour.nBlobs != SHOJI_NUM_BLOBS )
		return;

	// extract points from shoji
	for( int i=0; i < SHOJI_NUM_BLOBS; i++)
    {
        ofPoint corner;

        corner.x = ofMap(a_contour.blobs[i].centroid.x, 0, VIDEO_WIDTH, 0, ofGetWidth());
        corner.y = ofMap(a_contour.blobs[i].centroid.y, 0, VIDEO_HEIGHT, 0, ofGetHeight());

		m_pos[i] = corner;
    }

	sortPoints();
}

float QuadSurface::calcSurfaceArea() const
{
	// TODO:
	return 1.0f;
}

void QuadSurface::sortPoints()
{
	// calculate center, render out radians compared to center
	float radians[ SHOJI_NUM_BLOBS];
	const ofVec3f center = getCenterPos();

	for( int i = 0; i < SHOJI_NUM_BLOBS; i++)
    {
		ofVec3f diff = m_pos[i] - center;
		radians[i] = atan2f( diff.y, diff.x );
    }

	// sort pts by radians
	for( int i = 0; i < SHOJI_NUM_BLOBS-1; ++i )
    {
		for( int j = i+1; j < SHOJI_NUM_BLOBS; ++j )
		{
			if ( radians[j] < radians[i] )
			{
				SWAP( radians[i], radians[j] );
				SWAP( m_pos[i], m_pos[j] );
			}
		}
    }
}

ofPoint QuadSurface::getCenterPos() const
{
	ofPoint pt = ofPoint(0.0f);

	for( int i=0; i< SHOJI_NUM_BLOBS; i++)
    {
		pt += m_pos[i];
    }

	return pt / SHOJI_NUM_BLOBS;
}

void QuadSurface::setup()
{
	memset( m_pos, 0, sizeof(m_pos) ); 
}

void QuadSurface::draw()
{
	ofSetColor( 255, 0, 0 );
	ofFill();
	ofSetLineWidth(5.0f);

	for ( int i = 0; i < SHOJI_NUM_BLOBS; ++i )
	{
		auto pos = m_pos[i];

		ofSetColor( 0, 255, 0 );
		ofLine( m_pos[i], m_pos[ (i+1)%SHOJI_NUM_BLOBS ] );

		ofSetColor( 255, 0, 0 );
		ofCircle( pos, 10.0f );

		// print index
		char buffer[64];
		sprintf( buffer, "[%d] (%d,%d)", i, int(pos.x), int(pos.y) );
		std::string str_number = buffer;
		ofDrawBitmapString( str_number,  pos + ofPoint(0.0f,20.0f,0.0f) );
	}

	ofSetLineWidth(1.0f);
}

void QuadSurface::drawMask()
{
	auto centerPos = getCenterPos();

	ofSetColor( 255,0,0, 150);
	ofFill();

	for ( int i = 0; i < SHOJI_NUM_BLOBS; ++i )
	{
		auto pos_0 = m_pos[i];
		auto pos_1 = m_pos[(i+1)% SHOJI_NUM_BLOBS];
		auto dir_0 = pos_0 - centerPos;
		auto dir_1 = pos_1 - centerPos;

		auto pos_0_out = pos_0 + dir_0 * 10000.0f;
		auto pos_1_out = pos_1 + dir_1 * 10000.0f;

		ofTriangle( pos_0, pos_1, pos_1_out );
		ofTriangle( pos_0, pos_1_out , pos_0_out );
	}
}
