#include <pangolin/pangolin.h>
#include <Eigen/Dense>
#include <iostream>
#include <string.h>

using namespace std;

/**
 * @brief type of draw:
 *      LINE - only lines
 *      FILL - onli filled
 *      FULL - lines and filled
 * 
 */
enum drawType{
    LINE,
    FILL,
    FULL
};

/**
 * @brief Get the Sephere Point 
 * 
 * @param lat 
 * @param lon 
 * @param radius 
 * @return Eigen::Vector3f 
 */
Eigen::Vector3f getSepherePoint(float lat, float lon, float radius){
    Eigen::Vector3f point;
    // OpenGL坐标系y向上x向右
    point.z() = radius * sin(lat);
    point.x() = radius * cos(lat) * cos(lon);
    point.y() = radius * cos(lat) * sin(lon);

    return point;
}

/**
 * @brief draw half sephere 
 * 
 * @param x - origin x 
 * @param y  - origin y
 * @param radius 
 * @param type  - LINE, FILL or FULL
 */
void drawHalfSephere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, enum drawType type){

    const int lat_cnt = 30;
    const int lon_cnt = 60;
    

    const float lat_tau = (float)M_PI / lat_cnt; // 半球维度间隔
    const float lon_tau = 2. * (float)M_PI / lon_cnt; // 半球经度间隔

    GLfloat gl_vertics[6 * 3 * lat_cnt * lon_cnt];
    
    Eigen::Vector3f origin(x, y, z);

    int offset = 0;
    for (int i = 0; i < lat_cnt; i++){
        for(int j = 0; j < lon_cnt; j ++){
            Eigen::Vector3f pt0 = origin + getSepherePoint(i * lat_tau, j * lon_tau, radius);        
            Eigen::Vector3f pt1 = origin + getSepherePoint((i + 1) * lat_tau, j * lon_tau, radius);        
            Eigen::Vector3f pt2 = origin + getSepherePoint(i * lat_tau, (j + 1) * lon_tau, radius);        
            Eigen::Vector3f pt3 = origin + getSepherePoint((i + 1) * lat_tau, (j + 1) * lon_tau, radius);
            // 第一组三角片
            memcpy(gl_vertics + offset, pt0.data(), 3 * sizeof(float));
            offset += 3;            
            memcpy(gl_vertics + offset, pt3.data(), 3 * sizeof(float));
            offset += 3;
            memcpy(gl_vertics + offset, pt2.data(), 3 * sizeof(float));
            offset += 3;
            // 第二组三角片
            memcpy(gl_vertics + offset, pt0.data(), 3 * sizeof(float));
            offset += 3;            
            memcpy(gl_vertics + offset, pt1.data(), 3 * sizeof(float));
            offset += 3;
            memcpy(gl_vertics + offset, pt2.data(), 3 * sizeof(float));
            offset += 3;

            // for(int i = 0; i < offset ; i+=3){
                // std::cout << "gl_vertics " << i << ": " 
                        // << gl_vertics[i] << " " 
                        // << gl_vertics[i+1] << " "
                        // << gl_vertics[i+2] << std::endl; 
            // }
        }
    }
    // 参数依次为用于描述顶点的参数个数，参数类型，每个顶点间的唯一（0表示连续），顶点数组
    glVertexPointer(3, GL_FLOAT, 0, gl_vertics);
    glEnableClientState(GL_VERTEX_ARRAY);
    glLineWidth(1.0);
    switch (type)
    {
    case LINE:
        glColor4f(0.45f, 0.45f, 0.45f, 0.8f);
        glDrawArrays(GL_LINE_STRIP, 0, 6 * lat_cnt * lon_cnt);
        break;
    case FILL:
        glColor4f(0.76f, 0.76f, 0.76f, 0.2f);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 6 * lat_cnt * lon_cnt);
        break;
    case FULL:
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

        glColor4f(0.45f, 0.45f, 0.45f, 0.8f);
        glDrawArrays(GL_LINE_STRIP, 0, 6 * lat_cnt * lon_cnt);
        glColor4f(0.76f, 0.76f, 0.76f, 0.2f);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 6 * lat_cnt * lon_cnt);
        break;
    }
    glDisableClientState(GL_VERTEX_ARRAY);

}

void drawSephere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, enum drawType type){

    const int lat_cnt = 30;
    const int lon_cnt = 60;
    

    const float lat_tau = 2. * (float)M_PI / lat_cnt; // 半球维度间隔
    const float lon_tau = 2. * (float)M_PI / lon_cnt; // 半球经度间隔

    GLfloat gl_vertics[6 * 3 * lat_cnt * lon_cnt];

    Eigen::Vector3f origin(x, y, z);

    int offset = 0;
    for (int i = 0; i < lat_cnt; i++){
        for(int j = 0; j < lon_cnt; j ++){
            Eigen::Vector3f pt0 = origin + getSepherePoint(i * lat_tau, j * lon_tau, radius);        
            Eigen::Vector3f pt1 = origin + getSepherePoint((i + 1) * lat_tau, j * lon_tau, radius);        
            Eigen::Vector3f pt2 = origin + getSepherePoint(i * lat_tau, (j + 1) * lon_tau, radius);        
            Eigen::Vector3f pt3 = origin + getSepherePoint((i + 1) * lat_tau, (j + 1) * lon_tau, radius);
            // 第一组三角片
            memcpy(gl_vertics + offset, pt0.data(), 3 * sizeof(float));
            offset += 3;            
            memcpy(gl_vertics + offset, pt3.data(), 3 * sizeof(float));
            offset += 3;
            memcpy(gl_vertics + offset, pt2.data(), 3 * sizeof(float));
            offset += 3;
            // 第二组三角片
            memcpy(gl_vertics + offset, pt0.data(), 3 * sizeof(float));
            offset += 3;            
            memcpy(gl_vertics + offset, pt1.data(), 3 * sizeof(float));
            offset += 3;
            memcpy(gl_vertics + offset, pt2.data(), 3 * sizeof(float));
            offset += 3;

            // for(int i = 0; i < offset ; i+=3){
                // std::cout << "gl_vertics " << i << ": " 
                        // << gl_vertics[i] << " " 
                        // << gl_vertics[i+1] << " "
                        // << gl_vertics[i+2] << std::endl; 
            // }
        }
    }
    // 参数依次为用于描述顶点的参数个数，参数类型，每个顶点间的唯一（0表示连续），顶点数组
    glVertexPointer(3, GL_FLOAT, 0, gl_vertics);
    glEnableClientState(GL_VERTEX_ARRAY);
    glLineWidth(1.0);
    switch (type)
    {
    case LINE:
        glColor4f(0.45f, 0.45f, 0.45f, 0.8f);
        glDrawArrays(GL_LINE_STRIP, 0, 6 * lat_cnt * lon_cnt);
        break;
    case FILL:
        glColor4f(0.76f, 0.76f, 0.76f, 0.2f);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 6 * lat_cnt * lon_cnt);
        break;
    case FULL:
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

        glColor4f(0.45f, 0.45f, 0.45f, 0.8f);
        glDrawArrays(GL_LINE_STRIP, 0, 6 * lat_cnt * lon_cnt);
        glColor4f(0.76f, 0.76f, 0.76f, 0.2f);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 6 * lat_cnt * lon_cnt);
        break;
    }
    glDisableClientState(GL_VERTEX_ARRAY);

}

/**
 * @brief draw a fixed camera with scale
 * 
 * @param scale 
 */
void drawCam(const float scale=1.0){

    if(scale < 0){
        cerr << "scale should be positive !\n";
        return;
    }
        
    const float w = 1 * scale;
    const float h = w * 0.75;
    const float z = w * 0.8;

    glLineWidth(2 * scale);
    // 绘制相机轮廓线
    glBegin(GL_LINES);
    glColor3f(0.0f,1.0f,1.0f);
	glVertex3f(0,0,0);		glVertex3f(h,w,z);
	glVertex3f(0,0,0);		glVertex3f(h,-w,z);
	glVertex3f(0,0,0);		glVertex3f(-h,-w,z);
	glVertex3f(0,0,0);		glVertex3f(-h,w,z);
	glVertex3f(h,w,z);		glVertex3f(h,-w,z);
	glVertex3f(-h,w,z);		glVertex3f(-h,-w,z);
	glVertex3f(-h,w,z);		glVertex3f(h,w,z);
	glVertex3f(-h,-w,z);    glVertex3f(h,-w,z);
	glEnd();

    return;
}

/**
 * @brief draw a cam moving with pose
 * 
 * @param pos 
 * @param quat 
 */
void drawCamWithPose(Eigen::Vector3d &pos, Eigen::Quaterniond &quat){

    Eigen::Matrix3d R = quat.toRotationMatrix();

    glPushMatrix();
    std::vector<GLdouble> Twc = {R(0, 0), R(1,0), R(2, 0), 0.,
                                R(0, 1), R(1, 1), R(2, 1), 0.,
                                R(0, 2), R(1, 2), R(2, 2), 0.,
                                pos.x(), pos.y(), pos.z(), 1.};
    glMultMatrixd(Twc.data());
    drawCam();
    glPopMatrix();
}

/**
 * @brief draw a coordinate(origin is (0, 0, 0)) with scale
 * 
 * @param scale 
 */
void drawCoordinate(float scale = 1.0){
    // 绘制坐标系
    glLineWidth(2.0 * scale);
    glBegin ( GL_LINES );
	glColor3f ( 1.0f,0.f,0.f );
	glVertex3f( 0,0,0 );
	glVertex3f( scale,0,0 );
	glColor3f( 0.f,1.0f,0.f);
	glVertex3f( 0,0,0 );
	glVertex3f( 0,scale,0 );
	glColor3f( 0.f,0.f,1.f);
	glVertex3f( 0,0,0 );
	glVertex3f( 0,0,scale );
	glEnd();
}

/**
 * @brief draw trajectory 
 * 
 * @param traj 
 * @param scale: divide by scale
 */
void drawTraj(vector<Eigen::Vector3d> &traj, double scale = 1.){
   
    // glLineWidth(2);
    glBegin(GL_LINES);
    // glColor3f(1.0f, 0.5f, 0.f);
    for(size_t i=0; i<traj.size() - 1; i++){
        glVertex3d(traj[i].x() / scale, traj[i].y() / scale, traj[i].z() / scale);
        glVertex3d(traj[i+1].x() / scale, traj[i+1].y() / scale, traj[i+1].z() / scale);
    }
    glEnd();
}

void drawFlag(float scale = 1.0){
    glLineWidth(8 * scale);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 0.f);
    glVertex3f(0., 0., 0.);
    glVertex3f(0., 0., 3. * scale);
    glVertex3f(1.5 * scale, 0., 3. * scale);
    glVertex3f(1.5 * scale, 0., 2. * scale);
    glVertex3f(0., 0., 2. * scale);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(0., 0., 3. * scale);
    glVertex3f(1.5 * scale, 0., 3. * scale);
    glVertex3f(1.5 * scale, 0., 2. * scale);
    glVertex3f(0., 0., 2. * scale);
    glEnd();
}

void drawLandingSite(double lat, double lon, double radius){
    Eigen::Vector3f twb;
    Eigen::Matrix3f Rwb;

    Eigen::AngleAxisf rot_1(M_PI / 2.0 - lat, Eigen::Vector3f(1,0,0));
    Eigen::AngleAxisf rot_2(-lon, Eigen::Vector3f(0,1,0));
    Eigen::AngleAxisf rot_3(M_PI / 2, Eigen::Vector3f(0,1,0));

    Rwb = rot_3.matrix() * rot_2.matrix() * rot_1.matrix();


    twb = getSepherePoint(lat, lon, radius);

    // OpenGL是旋转矩阵不是变换矩阵
    glPushMatrix();
    std::vector<GLfloat> Twc = {Rwb(0, 0), Rwb(1,0), Rwb(2, 0), 0.,
                                Rwb(0, 1), Rwb(1, 1), Rwb(2, 1), 0.,
                                Rwb(0, 2), Rwb(1, 2), Rwb(2, 2), 0.,
                                twb.x(), twb.y(), twb.z(), 1.};
    glMultMatrixf(Twc.data());
    drawFlag(0.3);
    drawCoordinate(0.5);
    glPopMatrix();
}

void drawCube(GLfloat axis_min=-0.5f, GLfloat axis_max = +0.5f)
{
    const GLfloat l = axis_min;
    const GLfloat h = axis_max;
    
    // const GLfloat verts[] = {
    //     l,l,h,  h,l,h,  l,h,h,  h,h,h,  // FRONT
    //     l,l,l,  l,h,l,  h,l,l,  h,h,l,  // BACK
    //     l,l,h,  l,h,h,  l,l,l,  l,h,l,  // LEFT
    //     h,l,l,  h,h,l,  h,l,h,  h,h,h,  // RIGHT
    //     l,h,h,  h,h,h,  l,h,l,  h,h,l,  // TOP
    //     l,l,h,  l,l,l,  h,l,h,  h,l,l   // BOTTOM
    // };
    
    const GLfloat verts[] = {
        l,l,h,  h,l,h,  h,h,h,  l,h,h,  // FRONT
        l,l,l,  l,h,l,  h,h,l,  h,l,l,  // BACK
        l,l,h,  l,h,h,  l,h,l,  l,l,l,  // LEFT
        h,l,l,  h,h,l,  h,h,h,  h,l,h,  // RIGHT
        l,h,h,  h,h,h,  h,h,l,  l,h,l,  // TOP
        l,l,h,  l,l,l,  h,l,l,  h,l,h   // BOTTOM
    };
    
    glLineWidth(3);
    glVertexPointer(3, GL_FLOAT, 0, verts);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glColor4f(0.76f, 0.76f, 0.76f, 1.0f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    glDrawArrays(GL_LINE_STRIP, 0, 4);
    glDrawArrays(GL_LINE_STRIP, 4, 4);
    
    glColor4f(0.76f, 0.76f, 0.76f, 1.0f);
    glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    glDrawArrays(GL_LINE_STRIP, 8, 4);
    glDrawArrays(GL_LINE_STRIP, 12, 4);
    
    glColor4f(0.76f, 0.76f, 0.76f, 1.0f);
    glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 20, 4);
    glColor4f(0.45f, 0.45f, 0.45f, 1.0f);
    glDrawArrays(GL_LINE_STRIP, 16, 4);
    glDrawArrays(GL_LINE_STRIP, 20, 4);
    

    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawLander(double scale=1.0){
    glScaled(1.0, 1.5, 1.2);
    // drawHalfSephere(0., 0., 1., scale, FULL);
    drawCube(-scale, scale);

    glScaled(1.0, 1.0, 1.0);
    const float w = 1 * scale;
    const float h = w * 0.75;
    const float z = w * 0.8;

    glLineWidth(2);
    // 绘制相机轮廓线
    glBegin(GL_LINES);
    glColor3f(0.0f,1.0f,1.0f);
	glVertex3f(0,0,0-scale);		glVertex3f(h,w,-z-scale);
	glVertex3f(0,0,0-scale);		glVertex3f(h,-w,-z-scale);
	glVertex3f(0,0,0-scale);		glVertex3f(-h,-w,-z-scale);
	glVertex3f(0,0,0-scale);		glVertex3f(-h,w,-z-scale);
	glVertex3f(h,w,-z-scale);		glVertex3f(h,-w,-z-scale);
	glVertex3f(-h,w,-z-scale);		glVertex3f(-h,-w,-z-scale);
	glVertex3f(-h,w,-z-scale);		glVertex3f(h,w,-z-scale);
	glVertex3f(-h,-w,-z-scale);    glVertex3f(h,-w,-z-scale);
	glEnd();
}

void drawLanderWithPose(Eigen::Vector3d &pos, Eigen::Quaterniond &quat, double trajScale, double landerScale=1.0){

    Eigen::Matrix3d R = quat.toRotationMatrix(); 

    glPushMatrix();
    std::vector<GLdouble> Twc = {R(0, 0), R(1,0), R(2, 0), 0.,
                                R(0, 1), R(1, 1), R(2, 1), 0.,
                                R(0, 2), R(1, 2), R(2, 2), 0.,
                                pos.x() / trajScale, pos.y() / trajScale, pos.z() / trajScale, 1.};
    glMultMatrixd(Twc.data());
    drawLander(landerScale);
    glPopMatrix();
}

void drawBeaconWithStatus(vector<Eigen::Vector3d> &all_locations, vector<bool> &all_status, double scale){
    vector<Eigen::Vector3d> visible_beacons;
    vector<Eigen::Vector3d> unvisible_beacons;

    if(all_locations.size() != all_status.size()){
        cerr << "status size is not equal to beacon size !\n";
    }

    for (int i=0; i < all_locations.size(); i++){
        if(all_status[i]){
            visible_beacons.emplace_back(all_locations[i]);
        }
        else{
            unvisible_beacons.emplace_back(all_locations[i]);
        }
    }
    // cout << "visible beacons: " << visible_beacons.size() << endl << "unvisible beacons: " << unvisible_beacons.size() << endl;
    // draw visible beacons
    glColor3f(0.f, 1.0f, 0.0f);
    for (auto it : visible_beacons){
        GLfloat x = (float)it.x() / scale;
        GLfloat y = (float)it.y() / scale;

        pangolin::glDrawCircle(x, y, 50. / scale);
    }
    // draw unvisible beacons
    glColor3f(1.f, 0.0f, 0.0f);
    for (auto it : unvisible_beacons){
        Eigen::Vector2d p(it.x() / scale, it.y() / scale);
        pangolin::glDrawCircle(p, 50. / scale);
    }
}

void drawAllBeaconLocations(vector<Eigen::Vector3d> &all_locations, double scale){
    glColor3f(1.0f, 0.f, 0.f);
    for (auto it : all_locations){
        Eigen::Vector2d p(it.x() / scale, it.y() / scale);
        pangolin::glDrawCircle(p, 50. / scale);
    }
}
