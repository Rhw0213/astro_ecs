#pragma once

#include <cmath>
#include <vector>
#include <memory>
#include <algorithm>

#include "Entity.h"
#include "Component.h"
#include "PositionComponent.h"
#include "RotationComponent.h"
#include "OrbitComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "Random.h"

class Asteroid : public Entity {
public:
    Asteroid(float x, float y, float radius, float rotationSpeed, float orbitRadius, float orbitSpeed);
    void Init();

private:
    float m_radius;
    float m_rotationSpeed;
    float m_orbitRadius;
    float m_orbitSpeed;
};

Asteroid::Asteroid(float x, float y, float radius, float rotationSpeed, float orbitRadius, float orbitSpeed)
    : Entity("Asteroid"), m_radius(radius), m_rotationSpeed(rotationSpeed), m_orbitRadius(orbitRadius), m_orbitSpeed(orbitSpeed) {
    // 위치 컴포넌트 추가
    auto position = std::make_shared<PositionComponent>(x, y);
    AddComponent(position);

    // 회전 컴포넌트 추가
    auto rotation = std::make_shared<RotationComponent>(0.0f);
    AddComponent(rotation);

    // 궤도 컴포넌트 추가
    auto orbit = std::make_shared<OrbitComponent>(orbitRadius, orbitSpeed);
    AddComponent(orbit);

    // 충돌 컴포넌트 추가
    auto collision = std::make_shared<CollisionComponent>(radius);
    AddComponent(collision);

    // 렌더링 컴포넌트 추가
    auto render = std::make_shared<RenderComponent>();
    AddComponent(render);

    // 초기화
    Init();
}

void Asteroid::Init() {
    // 렌더링 컴포넌트 가져오기
    auto render = GetComponent<RenderComponent>();
    if (!render) return;

    // 기존 점들 초기화
    render->points.clear();

    // 꼭지점 개수 (6~12 사이의 랜덤 값)
    int numVertices = 6 + Random::randInt(0, 6);
    
    // 각 꼭지점의 각도와 거리 계산
    for (int i = 0; i < numVertices; i++) {
        // 각도 계산 (더 큰 랜덤 오프셋 추가)
        float angle = (2.0f * PI * i / numVertices) + Random::randFloat(-0.3f, 0.3f);
        
        // 중심으로부터의 거리 계산 (더 큰 랜덤성 추가)
        float distance = m_radius * (0.7f + Random::randFloat(-0.4f, 0.4f));
        
        // 최소 거리 보장
        distance = std::max(distance, m_radius * 0.5f);
        
        // 점 추가
        render->points.push_back({
            distance * cos(angle),
            distance * sin(angle)
        });
    }
} 