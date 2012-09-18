#ifndef __FuriousBlocksCoreDefaults_H_
#define __FuriousBlocksCoreDefaults_H_

#include <cstdint>

class FuriousBlocksCoreDefaults {
private:
protected:
public:
  static constexpr int32_t BLOCK_LOGICALHEIGHT = 16;
  static constexpr int32_t BLOCK_SWITCHINGTIME = 1;
  static constexpr int32_t BLOCK_HOVERINGTIME = 8;
  static constexpr int32_t BLOCK_AIRBOUNCINGTIME = 16;
  static constexpr int32_t BLOCK_BLINKINGTIME = 46;
  static constexpr int32_t BLOCK_REVEALINGTIMEBASE = 26;
  static constexpr int32_t BLOCK_REVEALINGTIMEINCREMENT = 10;
  static constexpr int32_t PANEL_WIDTH = 6;
  static constexpr int32_t PANEL_HEIGHT = 9;
  static constexpr int32_t PANEL_QUAKINGTIME = 64;
  static constexpr float CORE_FREQUENCY = 60;
};

#endif //__FuriousBlocksCoreDefaults_H_
