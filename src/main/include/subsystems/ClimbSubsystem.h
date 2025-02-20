#pragma once

#include <rev/SparkMax.h>
#include <rev/SparkRelativeEncoder.h>

#include "frc/kinematics/SwerveModulePosition.h"
#include "frc/kinematics/SwerveModuleState.h"
#include <frc/Compressor.h>
#include <frc/DigitalInput.h>
#include <frc/PneumaticsModuleType.h>
#include <frc/Solenoid.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/Command.h>
#include <frc2/command/SubsystemBase.h>
#include <optional>
#include <frc2/command/Command.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/SwerveControllerCommand.h>
// //try to implicitly include units etc argh cpp is annoying ill try to add
// a style checker or smth #include <units/voltage.h>

using namespace rev::spark;

class ClimbSubsystem : public frc2::SubsystemBase {
  /**
   * Constructs the Climbing subsystem and configures hardware, I.e
   * encoder, and PID controller.
   */
public:
  ClimbSubsystem();
  ~ClimbSubsystem() {}

  frc2::Command *Trigger();
  frc2::Command *m_null_command;


  frc2::Command *Unspool();
  frc2::Command *m_unspool_command;
  frc2::Command *Spool();
  frc2::Command *m_spool_command;
  void PneumaticUp();
  void PneumaticDown();
  bool TestSensorUp();
  bool TestSensorDown();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void Stop();

private:
  enum Stage
  {
    STAGE_DOWN,
    STAGE_GOING_UP,
    STAGE_UP,
    STAGE_GOING_DOWN
  } stage = STAGE_DOWN;

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  SparkMax m_climbingMotor;

  SparkRelativeEncoder m_climbingEncoder = m_climbingMotor.GetEncoder();

  SparkClosedLoopController m_climbingClosedLoopController =
      m_climbingMotor.GetClosedLoopController();

  frc::Solenoid solenoid{frc::PneumaticsModuleType::CTREPCM,
                         0}; // Solenoid on channel 0
  frc::Compressor compressor{
      frc::PneumaticsModuleType::CTREPCM}; // Compressor control

  // Pneumatics compressor
  frc::Compressor m_compressor;

  frc::DigitalInput upSensor;
  frc::DigitalInput downSensor;
};
