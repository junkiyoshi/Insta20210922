#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(3);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	this->fbo.readToPixels(this->pixels);
	this->pixels_mat = cv::Mat(this->pixels.getHeight(), this->pixels.getWidth(), CV_8UC4, this->pixels.getData());
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(914);

	this->fbo.begin();
	ofClear(0);
	ofFill();
	ofTranslate(this->fbo.getWidth() * 0.5, this->fbo.getHeight() * 0.5);

	ofColor color;
	for (int i = 0; i < 14; i++) {

		auto len = 23;
		auto radius = (i + 1) * 20;
		auto deg_start = 0;
		auto deg_param = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.008), 0, 1, 90, 360 + 120);
		if (deg_param > 360) { deg_param = 360; }
		auto deg_end = deg_start + deg_param;
		vector<glm::vec2> vertices_1, vertices_2;
		for (int deg = deg_start - 5; deg <= deg_end + 5; deg++) {

			vertices_1.push_back(glm::vec2((radius - len * 0.5) * cos(deg * DEG_TO_RAD), (radius - len * 0.5) * sin(deg * DEG_TO_RAD)));
			vertices_2.push_back(glm::vec2((radius + len * 0.5) * cos(deg * DEG_TO_RAD), (radius + len * 0.5) * sin(deg * DEG_TO_RAD)));
		}
		reverse(vertices_2.begin(), vertices_2.end());

		color.setHsb(ofRandom(255), 255, 255);
		ofSetColor(color);

		ofBeginShape();
		ofVertices(vertices_1);
		ofVertices(vertices_2);
		ofEndShape(true);
	}

	this->fbo.end();
	this->fbo.readToPixels(this->pixels);

	cv::GaussianBlur(this->pixels_mat, this->pixels_mat, cv::Size(49, 49), 50, 50);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSeedRandom(914);

	ofFill();
	ofSetColor(255);
	ofImage draw_image;
	draw_image.setFromPixels(this->pixels);
	draw_image.draw(0, 0);

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofColor color;
	for (int i = 0; i < 14; i++) {

		auto len = 8;
		auto radius = (i + 1) * 20;
		auto deg_start = 0;
		auto deg_param = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.008), 0, 1, 90, 360 + 120);
		if (deg_param > 360) { deg_param = 360; }
		auto deg_end = deg_start + deg_param;
		vector<glm::vec2> vertices_1, vertices_2;
		for (int deg = deg_start; deg <= deg_end; deg++) {

			vertices_1.push_back(glm::vec2((radius - len * 0.5) * cos(deg * DEG_TO_RAD), (radius - len * 0.5) * sin(deg * DEG_TO_RAD)));
			vertices_2.push_back(glm::vec2((radius + len * 0.5) * cos(deg * DEG_TO_RAD), (radius + len * 0.5) * sin(deg * DEG_TO_RAD)));
		}
		reverse(vertices_2.begin(), vertices_2.end());

		color.setHsb(ofRandom(255), 255, 255);

		ofFill();
		ofSetColor(ofColor(255));
		ofBeginShape();
		ofVertices(vertices_1);
		ofVertices(vertices_2);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(color);
		ofBeginShape();
		ofVertices(vertices_1);
		ofVertices(vertices_2);
		ofEndShape(true);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}