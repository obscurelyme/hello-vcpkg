#include <gtest/gtest.h>
#include <raylib.h>

#include "Editor/core.h"

class GuiWindowTest : public ::testing::Test {
  protected:
    void SetUp() override {
      InitWindow(1024, 720, "Editor test suite");
      if (!IsWindowReady()) {
        CloseWindow();
        FAIL() << "Window was not initialized";
      }
      editor = new Zero::Editor();
      BeginDrawing();
      ClearBackground(BLACK);
      editor->beginRender();
    }

    void TearDown() override {
      editor->endRender();
      EndDrawing();

      editor->cleanUp();
      CloseWindow();
    }

  private:
    Zero::Editor* editor;
};

TEST_F(GuiWindowTest, DrawsAWindow) {
  Zero::GuiPanel window{"Test Window"};
  window.draw();
  EXPECT_EQ(window.title, "Test Window");
}