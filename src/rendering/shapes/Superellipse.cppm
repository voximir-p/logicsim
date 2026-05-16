module;

#include <SFML/Graphics/Shape.hpp>

export module rendering.shapes.Superelipse;

constexpr float normalize(
    const float value,
    const float inMin,
    const float inMax
) noexcept {
    return 2.f * (value - inMin) / (inMax - inMin) - 1.f;
}

constexpr float signOf(const float value) noexcept {
    if (value > 0.f) return 1.f;
    if (value < 0.f) return -1.f;
    return 0.f;
}

float easeCorners(const float x) noexcept {
    // Cubic easing:
    // dedicate more vertices to corners
    return (1.f - std::pow(1.f - std::abs(x), 3.f)) * signOf(x);
}

export class Superellipse : public sf::Shape {
public:
    explicit Superellipse(
        float exponent = 4,
        std::size_t resolution = 20
    ) : m_exponent(std::max(exponent, 0.01f))
        , m_resolution(std::max<std::size_t>(resolution, 2))
        , m_radius(std::min(m_height, m_width)) {
    }

    void setSize(const sf::Vector2f &size) {
        m_width = std::max(size.x, 0.f);
        m_height = std::max(size.y, 0.f);
        updateRadius();
        update();
    }

    void setExponent(float exponent) {
        m_exponent = std::max(exponent, 0.01f);
        updateRadius();
        update();
    }

    float getExponent() const {
        return m_exponent;
    }

    void setResolution(std::size_t resolution) {
        m_resolution = std::max<std::size_t>(resolution, 2);
        updateRadius();
        update();
    }

    std::size_t getResolution() const {
        return m_resolution;
    }

    std::size_t getPointCount() const override {
        return m_resolution * 4;
    }

    sf::Vector2f getPoint(std::size_t index) const override {
        const std::size_t half = m_resolution * 2;
        const std::size_t localIndex = index % half;

        // Bottom half is mirrored to preserve clockwise winding
        const float ySign = index >= half ? -1.f : 1.f;

        float x = normalize(
            static_cast<float>(localIndex),
            0.f,
            static_cast<float>(half)
        );

        x = easeCorners(x) * ySign;
        x *= m_radius;

        const float normalizedX = std::abs(x / m_radius);
        const float exponent = std::pow(normalizedX, m_exponent);

        float y = m_radius * std::pow(1.f - exponent, 1.f / m_exponent) * ySign;

        if (m_width > m_height) {
            x += (x >= 0.f ? 1.f : -1.f) * (m_width - m_radius);
        } else {
            y += (y >= 0.f ? 1.f : -1.f) * (m_height - m_radius);
        }

        return {x, y};
    }

private:
    float m_width{};
    float m_height{};
    float m_exponent;
    std::size_t m_resolution;

    float m_radius;

    void updateRadius() {
        m_radius = std::min(m_height, m_width);
    }
};
