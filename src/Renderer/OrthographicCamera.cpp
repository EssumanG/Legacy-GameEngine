#include "lg_pch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Legacy 
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        :m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
    {
        LG_PROFILE_FUNCTION();
        
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
    void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
    {
        LG_PROFILE_FUNCTION();
        
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
    void OrthographicCamera::RecalculationViewMatrix()
    {
        LG_PROFILE_FUNCTION();
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0), m_Position) * 
        glm::rotate(glm::mat4(1.0), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
        
        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        
    }
}