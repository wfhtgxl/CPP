#include <boost/test/unit_test.hpp>
#include <memory>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include <cmath>

const double accuracy = 0.00001;

// =====================test initialization shape=====================
BOOST_AUTO_TEST_SUITE(InitializeShape)

    BOOST_AUTO_TEST_CASE(InitializeShape_DefaultConstructors)
    {
      jianing::CompositeShape com_shape;

      BOOST_REQUIRE_EQUAL(0, com_shape.getSize());
      BOOST_REQUIRE_EQUAL(3, com_shape.getCapacity());
      BOOST_REQUIRE_EQUAL(true, com_shape.empty());
      BOOST_REQUIRE_EQUAL(0.0, com_shape.getArea());

      BOOST_REQUIRE_THROW(com_shape.getCenter().x, std::logic_error);
      BOOST_REQUIRE_THROW(com_shape.getCenter().y, std::logic_error);
      BOOST_REQUIRE_THROW(com_shape.removeShape(0), std::logic_error);
      BOOST_REQUIRE_THROW(com_shape.printShape(), std::domain_error);
      BOOST_REQUIRE_THROW(com_shape.scale(0), std::domain_error);
    }

    BOOST_AUTO_TEST_CASE(InitializeShape_DefaultParameterConstructorOnCorrectShape_NoError)
    {
      // init
      jianing::point_t center = {1.1, 2.2};
      double r_cirle = 3.3;
      jianing::Shape::ShapePtr circle = std::make_shared<jianing::Circle>(center, r_cirle);

      jianing::CompositeShape com_shape;
      com_shape.pushShape(circle);

      BOOST_REQUIRE_EQUAL(1, com_shape.getSize());
      BOOST_REQUIRE_EQUAL(3, com_shape.getCapacity());
      BOOST_REQUIRE_EQUAL(false, com_shape.empty());

      BOOST_REQUIRE_CLOSE(1.1, com_shape.getCenter().x, accuracy);
      BOOST_REQUIRE_CLOSE(2.2, com_shape.getCenter().y, accuracy);
      BOOST_REQUIRE_CLOSE(M_PI * 3.3 * 3.3, com_shape.getArea(), accuracy);
    }

    BOOST_AUTO_TEST_CASE(InitializeShape_TestCopyConstructor_NoError)
    {
      jianing::point_t center = {1.1, 2.2};
      double r_cirle = 3.3;
      jianing::Shape::ShapePtr circle = std::make_shared<jianing::Circle>(center, r_cirle);

      jianing::CompositeShape old_com_shape;

      old_com_shape.pushShape(circle);

      jianing::CompositeShape new_com_shape = old_com_shape;

      BOOST_REQUIRE_EQUAL(1, new_com_shape.getSize());
      BOOST_REQUIRE_EQUAL(3, new_com_shape.getCapacity());
      BOOST_REQUIRE_EQUAL(false, new_com_shape.empty());

      BOOST_REQUIRE_CLOSE(1.1, new_com_shape.getCenter().x, accuracy);
      BOOST_REQUIRE_CLOSE(2.2, new_com_shape.getCenter().y, accuracy);
      BOOST_REQUIRE_CLOSE(M_PI * 3.3 * 3.3, new_com_shape.getArea(), accuracy);

      BOOST_REQUIRE_EQUAL(1, old_com_shape.getSize());
      BOOST_REQUIRE_EQUAL(3, old_com_shape.getCapacity());
      BOOST_REQUIRE_EQUAL(false, old_com_shape.empty());

      BOOST_REQUIRE_CLOSE(1.1, old_com_shape.getCenter().x, accuracy);
      BOOST_REQUIRE_CLOSE(2.2, old_com_shape.getCenter().y, accuracy);
      BOOST_REQUIRE_CLOSE(M_PI * 3.3 * 3.3, old_com_shape.getArea(), accuracy);
    }

BOOST_AUTO_TEST_SUITE_END()

// =====================test initialization shape(FrameRect)=====================
BOOST_AUTO_TEST_SUITE(TestFrameRectWhenInitializeShape)

  BOOST_AUTO_TEST_CASE(TestFrameRectWhenInitializeShape_DefaultConstructors_ThrowError)
  {
    jianing::CompositeShape com_shape;

    BOOST_REQUIRE_THROW(com_shape.getFrameRect().pos.x, std::logic_error);
    BOOST_REQUIRE_THROW(com_shape.getFrameRect().pos.y, std::logic_error);
    BOOST_REQUIRE_THROW(com_shape.getFrameRect().width, std::logic_error);
    BOOST_REQUIRE_THROW(com_shape.getFrameRect().height, std::logic_error);
  }

  BOOST_AUTO_TEST_CASE(TestFrameRectWhenInitializeShape_DefaultParameterConstructor_NoError)
  {
    jianing::point_t center = {1.1, 2.2};
    double r_cirle = 3.3;
    jianing::Shape::ShapePtr circle = std::make_shared<jianing::Circle>(center, r_cirle);

    jianing::CompositeShape com_shape;
    com_shape.pushShape(circle);

    BOOST_REQUIRE_CLOSE(1.1, com_shape.getFrameRect().pos.x, accuracy);
    BOOST_REQUIRE_CLOSE(2.2, com_shape.getFrameRect().pos.y, accuracy);
    BOOST_REQUIRE_CLOSE(3.3 * 2.0, com_shape.getFrameRect().width, accuracy);
    BOOST_REQUIRE_CLOSE(3.3 * 2.0, com_shape.getFrameRect().height, accuracy);
  }

  BOOST_AUTO_TEST_CASE(TestFrameRectWhenInitializeShape_TestCopyConstructor_NoError)
  {
    jianing::point_t center = {1.1, 2.2};
    double r_cirle = 3.3;
    jianing::Shape::ShapePtr circle = std::make_shared<jianing::Circle>(center, r_cirle);

    jianing::CompositeShape old_com_shape;
    old_com_shape.pushShape(circle);

    jianing::CompositeShape new_com_shape = old_com_shape;

    BOOST_REQUIRE_CLOSE(1.1, new_com_shape.getFrameRect().pos.x, accuracy);
    BOOST_REQUIRE_CLOSE(2.2, new_com_shape.getFrameRect().pos.y, accuracy);
    BOOST_REQUIRE_CLOSE(3.3 * 2.0, new_com_shape.getFrameRect().width, accuracy);
    BOOST_REQUIRE_CLOSE(3.3 * 2.0, new_com_shape.getFrameRect().height, accuracy);

    BOOST_REQUIRE_CLOSE(1.1, old_com_shape.getFrameRect().pos.x, accuracy);
    BOOST_REQUIRE_CLOSE(2.2, old_com_shape.getFrameRect().pos.y, accuracy);
    BOOST_REQUIRE_CLOSE(3.3 * 2.0, old_com_shape.getFrameRect().width, accuracy);
    BOOST_REQUIRE_CLOSE(3.3 * 2.0, old_com_shape.getFrameRect().height, accuracy);
  }

BOOST_AUTO_TEST_SUITE_END()

// =====================test function pushShape=====================
BOOST_AUTO_TEST_SUITE(TestpushShape)

    BOOST_AUTO_TEST_CASE(TestpushShape_PushCorrectShape_NoError)
    {
      jianing::point_t center = {1.1, 2.2};
      double r_cirle = 3.3;
      jianing::Shape::ShapePtr circle = std::make_shared<jianing::Circle>(center, r_cirle);

      jianing::CompositeShape com_shape;

      com_shape.pushShape(circle);

      BOOST_CHECK_EQUAL(1, com_shape.getSize());
      BOOST_CHECK_EQUAL(3, com_shape.getCapacity());
      BOOST_CHECK_EQUAL(false, com_shape.empty());
      BOOST_CHECK_CLOSE(1.1, com_shape.getCenter().x, accuracy);
      BOOST_CHECK_CLOSE(2.2, com_shape.getCenter().y, accuracy);
      BOOST_CHECK_CLOSE(M_PI * 3.3 * 3.3, com_shape.getArea(), accuracy);
    }

    BOOST_AUTO_TEST_CASE(TestpushShape_PushNullptr_ThrowError)
    {
      jianing::CompositeShape com_shape;

      BOOST_CHECK_THROW(com_shape.pushShape(nullptr), std::invalid_argument);
    }

BOOST_AUTO_TEST_SUITE_END()

// =====================test function pushShape(FrameRect)=====================
BOOST_AUTO_TEST_SUITE(TestFrameRectAfterpushShape)

    BOOST_AUTO_TEST_CASE(TestFrameRectAfterpushShape_PushCorrectShape_NoError)
    {
      jianing::point_t center = {1.1, 2.2};
      double r_cirle = 3.3;
      jianing::Shape::ShapePtr circle = std::make_shared<jianing::Circle>(center, r_cirle);

      jianing::CompositeShape com_shape;

      com_shape.pushShape(circle);

      BOOST_CHECK_CLOSE(1.1, com_shape.getFrameRect().pos.x, accuracy);
      BOOST_CHECK_CLOSE(2.2, com_shape.getFrameRect().pos.y, accuracy);
      BOOST_CHECK_CLOSE(3.3 * 2.0, com_shape.getFrameRect().width, accuracy);
      BOOST_CHECK_CLOSE(3.3 * 2.0, com_shape.getFrameRect().height, accuracy);
    }

BOOST_AUTO_TEST_SUITE_END()

// =====================test function removeShape=====================
BOOST_AUTO_TEST_SUITE(TestRemoveShape)

    BOOST_AUTO_TEST_CASE(TestRemoveShape_CorrectValueAfterPushShape_NoError)
    {
      jianing::CompositeShape com_shape;

      // push first shape
      jianing::point_t center = {1.2, 2.2};
      double r_cirle = 3.2;
      jianing::Shape::ShapePtr circle = std::make_shared<jianing::Circle>(center, r_cirle);

      com_shape.pushShape(circle);

      // push second shape
      jianing::rectangle_t center_width_height_rec = {5.1, 9.3, 13.6, 21.3};
      jianing::Shape::ShapePtr rectangle = std::make_shared<jianing::Rectangle>(center_width_height_rec);

      com_shape.pushShape(rectangle);

      //remove first shape
      com_shape.removeShape(0);

      BOOST_CHECK_EQUAL(1, com_shape.getSize());

      BOOST_CHECK_CLOSE(13.6, com_shape.getCenter().x, accuracy);
      BOOST_CHECK_CLOSE(21.3, com_shape.getCenter().y, accuracy);
      BOOST_CHECK_CLOSE(5.1 * 9.3, com_shape.getArea(), accuracy);

      //remove second shape
      com_shape.removeShape(0);

      BOOST_CHECK_EQUAL(0, com_shape.getSize());
      BOOST_CHECK_EQUAL(0.0, com_shape.getArea());

      BOOST_CHECK_THROW(com_shape.getCenter().x, std::logic_error);
      BOOST_CHECK_THROW(com_shape.getCenter().y, std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(TestRemoveShape_RemoveShapeWhenArrayEmpty_ThrowError)
    {
      jianing::CompositeShape com_shape;

      BOOST_CHECK_THROW(com_shape.removeShape(0), std::out_of_range);

      // push one shape
      jianing::point_t center = {4.5, 7.7};
      double r_cirle = 8.9;
      jianing::Shape::ShapePtr circle = std::make_shared<jianing::Circle>(center, r_cirle);

      com_shape.pushShape(circle);

      BOOST_CHECK_THROW(com_shape.removeShape(8), std::out_of_range);
    }

BOOST_AUTO_TEST_SUITE_END()

// =====================Test Frame Rect After Remove Shape=====================
BOOST_AUTO_TEST_SUITE(TestFrameRectAfterPushAndRemoveShape)

  BOOST_AUTO_TEST_CASE(TestFrameRectAfterRemoveShape_CorrectValueAfterPushShape_Noerror)
  {
    jianing::CompositeShape com_shape;

    // push first shape
    jianing::point_t center = {1.0, 2.0};
    double r_cirle = 1.0;
    jianing::Shape::ShapePtr circle = std::make_shared<jianing::Circle>(center, r_cirle);

    com_shape.pushShape(circle);

    BOOST_CHECK_CLOSE(1.0, com_shape.getFrameRect().pos.x, accuracy);
    BOOST_CHECK_CLOSE(2.0, com_shape.getFrameRect().pos.y, accuracy);
    BOOST_CHECK_CLOSE(1.0 + 1.0, com_shape.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE(1.0 + 1.0, com_shape.getFrameRect().height, accuracy);

    // push second shape
    jianing::rectangle_t center_width_height_rec = {1.0, 2.0, 0.5, 1.0};
    jianing::Shape::ShapePtr rectangle = std::make_shared<jianing::Rectangle>(center_width_height_rec);

    com_shape.pushShape(rectangle);

    BOOST_CHECK_CLOSE((1.0 + 1.0) / 2, com_shape.getFrameRect().pos.x, accuracy);
    BOOST_CHECK_CLOSE((1.0 + 2.0) / 2, com_shape.getFrameRect().pos.y, accuracy);
    BOOST_CHECK_CLOSE(1.0 + 1.0, com_shape.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE(1.0 + 2.0, com_shape.getFrameRect().height, accuracy);

    //remove first shape
    com_shape.removeShape(0);

    BOOST_CHECK_CLOSE(0.5, com_shape.getFrameRect().pos.x, accuracy);
    BOOST_CHECK_CLOSE(1.0, com_shape.getFrameRect().pos.y, accuracy);
    BOOST_CHECK_CLOSE(1.0, com_shape.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE(2.0, com_shape.getFrameRect().height, accuracy);

    //remove second shape
    com_shape.removeShape(0);

    BOOST_CHECK_THROW(com_shape.getFrameRect().pos.x, std::logic_error);
    BOOST_CHECK_THROW(com_shape.getFrameRect().pos.y, std::logic_error);
    BOOST_CHECK_THROW(com_shape.getFrameRect().width, std::logic_error);
    BOOST_CHECK_THROW(com_shape.getFrameRect().height, std::logic_error);
  }

BOOST_AUTO_TEST_SUITE_END()

// =====================Test size and capacity=====================
BOOST_AUTO_TEST_SUITE(TestSizeAndCapacity)

  BOOST_AUTO_TEST_CASE(TestSizeAndCapacity_OnCorrectValue_NoError)
  {
    jianing::CompositeShape com_shape;

    BOOST_CHECK_EQUAL(0, com_shape.getSize());
    BOOST_CHECK_EQUAL(3, com_shape.getCapacity());

    // push one shape
    jianing::rectangle_t first_center_width_height_rec = {3.3, 2.2, 3.5, 1.4};
    jianing::Shape::ShapePtr first_rectangle = std::make_shared<jianing::Rectangle>(first_center_width_height_rec);

    com_shape.pushShape(first_rectangle);

    BOOST_CHECK_EQUAL(1, com_shape.getSize());
    BOOST_CHECK_EQUAL(3, com_shape.getCapacity());

    // test resever
    com_shape.reserve(22);

    BOOST_CHECK_EQUAL(1, com_shape.getSize());
    BOOST_CHECK_EQUAL(22, com_shape.getCapacity());

    // reduce capacity
    com_shape.reserve(1);

    BOOST_CHECK_EQUAL(1, com_shape.getSize());
    BOOST_CHECK_EQUAL(1, com_shape.getCapacity());
    BOOST_CHECK_EQUAL(3.5, com_shape.getCenter().x);
    BOOST_CHECK_EQUAL(1.4, com_shape.getCenter().y);
    BOOST_CHECK_CLOSE(3.3 * 2.2, com_shape.getArea(), accuracy);
  }

BOOST_AUTO_TEST_SUITE_END()

// =====================Test scale shape=====================
BOOST_AUTO_TEST_SUITE(TestSacle)

  BOOST_AUTO_TEST_CASE(TestSacle_OnCorrectValue_NoError)
  {
  jianing::CompositeShape com_shape;

  // push first shape
  jianing::point_t center = {1.0, 1.0};
  double r_cirle = 1.0;
  jianing::Shape::ShapePtr circle = std::make_shared<jianing::Circle>(center, r_cirle);

  com_shape.pushShape(circle);

  // push second shape
  jianing::rectangle_t center_width_height_rec = {2.0, 4.0, 2.0, 2.0};
  jianing::Shape::ShapePtr rectangle = std::make_shared<jianing::Rectangle>(center_width_height_rec);

  com_shape.pushShape(rectangle);

  BOOST_CHECK_CLOSE((2.0 + 1.0) / 2.0, com_shape.getFrameRect().pos.x, accuracy);
  BOOST_CHECK_CLOSE((2.0 + 2.0) / 2.0, com_shape.getFrameRect().pos.y, accuracy);
  BOOST_CHECK_CLOSE(1.0 + 2.0, com_shape.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(4.0, com_shape.getFrameRect().height, accuracy);

  //remove first shape
  com_shape.scale(2.0);

  BOOST_CHECK_CLOSE((-1.5 + 4.5) / 2.0, com_shape.getFrameRect().pos.x, accuracy);
  BOOST_CHECK_CLOSE((-1.5 + 5.5) / 2.0, com_shape.getFrameRect().pos.y, accuracy);
  BOOST_CHECK_CLOSE(1.5 + 4.5, com_shape.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(2.5 + 5.5, com_shape.getFrameRect().height, accuracy);
  }

  BOOST_AUTO_TEST_CASE(TestSacle_OnValueOne_ShapeNoChange)
  {
    jianing::CompositeShape com_shape;

    // push first shape
    jianing::point_t center = {1.0, 2.0};
    double r_cirle = 1.0;
    jianing::Shape::ShapePtr circle = std::make_shared<jianing::Circle>(center, r_cirle);

    com_shape.pushShape(circle);

    BOOST_CHECK_CLOSE(1.0, com_shape.getFrameRect().pos.x, accuracy);
    BOOST_CHECK_CLOSE(2.0, com_shape.getFrameRect().pos.y, accuracy);
    BOOST_CHECK_CLOSE(1.0 + 1.0, com_shape.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE(1.0 + 1.0, com_shape.getFrameRect().height, accuracy);

    // push second shape
    jianing::rectangle_t center_width_height_rec = {1.0, 2.0, 0.5, 1.0};
    jianing::Shape::ShapePtr rectangle = std::make_shared<jianing::Rectangle>(center_width_height_rec);

    com_shape.pushShape(rectangle);

    com_shape.scale(1.0);

    BOOST_CHECK_CLOSE((1.0 + 1.0) / 2, com_shape.getFrameRect().pos.x, accuracy);
    BOOST_CHECK_CLOSE((1.0 + 2.0) / 2, com_shape.getFrameRect().pos.y, accuracy);
    BOOST_CHECK_CLOSE(1.0 + 1.0, com_shape.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE(1.0 + 2.0, com_shape.getFrameRect().height, accuracy);
  }

  BOOST_AUTO_TEST_CASE(TestSacle_OnWrongValue_ThrowError)
  {
    jianing::CompositeShape com_shape;

    jianing::point_t center = {2.5, 3.5};
    double r_cirle = 3.0;
    jianing::Shape::ShapePtr circle = std::make_shared<jianing::Circle>(center, r_cirle);

    com_shape.pushShape(circle);

    BOOST_CHECK_THROW(com_shape.scale(-2.3), std::domain_error);
  }

BOOST_AUTO_TEST_SUITE_END()

// =====================test rotate composize shape=====================
BOOST_AUTO_TEST_SUITE(TestSacleComposizeShape)

  BOOST_AUTO_TEST_CASE(TestSacleComposizeShape_InPositiveDirection_CorrectWigthHeightXYAfterRotate)
  {
  jianing::CompositeShape com_shape;

  // push first shape
  jianing::point_t circle_center = {1.0, 1.0};
  double r_cirle = 2.0;
  jianing::Shape::ShapePtr circle = std::make_shared<jianing::Circle>(circle_center, r_cirle);

  com_shape.pushShape(circle);

  // push second shape
  jianing::rectangle_t center_width_height_rec = {2.0, 4.0, 2.0, 2.0};
  jianing::Shape::ShapePtr rectangle = std::make_shared<jianing::Rectangle>(center_width_height_rec);

  com_shape.pushShape(rectangle);

  jianing::point_t center_rotation = com_shape.getCenter();
  const double area = com_shape.getArea();

  //remove first shape
  com_shape.rotate(30);

  const double cos = std::cos(2 * M_PI * 30 / 360);
  const double sin = std::sin(2 * M_PI * 30 / 360);

  // test cirle
  const double dx_circle = (circle_center.x - center_rotation.x) * cos - (circle_center.y - center_rotation.y) * sin;
  const double dy_ciecle = (circle_center.x - center_rotation.x) * sin + (circle_center.y - center_rotation.y) * cos;

  BOOST_CHECK_CLOSE(center_rotation.x + dx_circle, com_shape[0]->getFrameRect().pos.x, accuracy);
  BOOST_CHECK_CLOSE(center_rotation.y + dy_ciecle, com_shape[0]->getFrameRect().pos.y, accuracy);
  BOOST_CHECK_CLOSE(r_cirle * 2.0, com_shape[0]->getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(r_cirle * 2.0, com_shape[0]->getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(M_PI * r_cirle * r_cirle, com_shape[0]->getArea(), accuracy);

  // test rectangle
  const double dx_rectangle = (center_width_height_rec.pos.x - center_rotation.x) * cos - (center_width_height_rec.pos.y - center_rotation.y) * sin;
  const double dy_rectangle = (center_width_height_rec.pos.x - center_rotation.x) * sin + (center_width_height_rec.pos.y - center_rotation.y) * cos;
  const double width_rectange = center_width_height_rec.width * std::fabs(cos) + center_width_height_rec.height * std::fabs(sin);
  const double height_rectange = center_width_height_rec.height * std::fabs(cos) + center_width_height_rec.width * std::fabs(sin);

  BOOST_CHECK_CLOSE(center_rotation.x + dx_rectangle, com_shape[1]->getFrameRect().pos.x, accuracy);
  BOOST_CHECK_CLOSE(center_rotation.y + dy_rectangle, com_shape[1]->getFrameRect().pos.y, accuracy);
  BOOST_CHECK_CLOSE(width_rectange, com_shape[1]->getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(height_rectange, com_shape[1]->getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(center_width_height_rec.width * center_width_height_rec.height, com_shape[1]->getArea(), accuracy);

  // test all the composize shape
  const double top = com_shape[1]->getFrameRect().pos.y + com_shape[1]->getFrameRect().height / 2.0;
  const double bottom = com_shape[0]->getFrameRect().pos.y - com_shape[0]->getFrameRect().height / 2.0;
  const double left = com_shape[0]->getFrameRect().pos.x - com_shape[0]->getFrameRect().width / 2.0;
  const double right = com_shape[1]->getFrameRect().pos.x + com_shape[1]->getFrameRect().width / 2.0;

  BOOST_CHECK_CLOSE((right - left) / 2.0 + left, com_shape.getFrameRect().pos.x, accuracy);
  BOOST_CHECK_CLOSE((top - bottom) / 2.0 + bottom, com_shape.getFrameRect().pos.y, accuracy);
  BOOST_CHECK_CLOSE(right - left, com_shape.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(top - bottom, com_shape.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(area, com_shape.getArea(), accuracy);
  }

BOOST_AUTO_TEST_SUITE_END()
