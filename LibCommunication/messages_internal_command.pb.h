// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: messages_internal_command.proto

#ifndef PROTOBUF_messages_5finternal_5fcommand_2eproto__INCLUDED
#define PROTOBUF_messages_5finternal_5fcommand_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004002 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_messages_5finternal_5fcommand_2eproto();
void protobuf_AssignDesc_messages_5finternal_5fcommand_2eproto();
void protobuf_ShutdownFile_messages_5finternal_5fcommand_2eproto();

class CommandWheel;
class CommandKicker;
class CommandDribbler;
class CommandRobot;
class ToTransmission;

// ===================================================================

class CommandWheel : public ::google::protobuf::Message {
 public:
  CommandWheel();
  virtual ~CommandWheel();
  
  CommandWheel(const CommandWheel& from);
  
  inline CommandWheel& operator=(const CommandWheel& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const CommandWheel& default_instance();
  
  void Swap(CommandWheel* other);
  
  // implements Message ----------------------------------------------
  
  CommandWheel* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CommandWheel& from);
  void MergeFrom(const CommandWheel& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required uint32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);
  
  // required double speed = 2;
  inline bool has_speed() const;
  inline void clear_speed();
  static const int kSpeedFieldNumber = 2;
  inline double speed() const;
  inline void set_speed(double value);
  
  // @@protoc_insertion_point(class_scope:CommandWheel)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_speed();
  inline void clear_has_speed();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  double speed_;
  ::google::protobuf::uint32 id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_messages_5finternal_5fcommand_2eproto();
  friend void protobuf_AssignDesc_messages_5finternal_5fcommand_2eproto();
  friend void protobuf_ShutdownFile_messages_5finternal_5fcommand_2eproto();
  
  void InitAsDefaultInstance();
  static CommandWheel* default_instance_;
};
// -------------------------------------------------------------------

class CommandKicker : public ::google::protobuf::Message {
 public:
  CommandKicker();
  virtual ~CommandKicker();
  
  CommandKicker(const CommandKicker& from);
  
  inline CommandKicker& operator=(const CommandKicker& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const CommandKicker& default_instance();
  
  void Swap(CommandKicker* other);
  
  // implements Message ----------------------------------------------
  
  CommandKicker* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CommandKicker& from);
  void MergeFrom(const CommandKicker& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required double speed = 1;
  inline bool has_speed() const;
  inline void clear_speed();
  static const int kSpeedFieldNumber = 1;
  inline double speed() const;
  inline void set_speed(double value);
  
  // optional bool forced = 2 [default = false];
  inline bool has_forced() const;
  inline void clear_forced();
  static const int kForcedFieldNumber = 2;
  inline bool forced() const;
  inline void set_forced(bool value);
  
  // @@protoc_insertion_point(class_scope:CommandKicker)
 private:
  inline void set_has_speed();
  inline void clear_has_speed();
  inline void set_has_forced();
  inline void clear_has_forced();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  double speed_;
  bool forced_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_messages_5finternal_5fcommand_2eproto();
  friend void protobuf_AssignDesc_messages_5finternal_5fcommand_2eproto();
  friend void protobuf_ShutdownFile_messages_5finternal_5fcommand_2eproto();
  
  void InitAsDefaultInstance();
  static CommandKicker* default_instance_;
};
// -------------------------------------------------------------------

class CommandDribbler : public ::google::protobuf::Message {
 public:
  CommandDribbler();
  virtual ~CommandDribbler();
  
  CommandDribbler(const CommandDribbler& from);
  
  inline CommandDribbler& operator=(const CommandDribbler& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const CommandDribbler& default_instance();
  
  void Swap(CommandDribbler* other);
  
  // implements Message ----------------------------------------------
  
  CommandDribbler* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CommandDribbler& from);
  void MergeFrom(const CommandDribbler& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required double speed = 1;
  inline bool has_speed() const;
  inline void clear_speed();
  static const int kSpeedFieldNumber = 1;
  inline double speed() const;
  inline void set_speed(double value);
  
  // optional bool forced = 2 [default = false];
  inline bool has_forced() const;
  inline void clear_forced();
  static const int kForcedFieldNumber = 2;
  inline bool forced() const;
  inline void set_forced(bool value);
  
  // @@protoc_insertion_point(class_scope:CommandDribbler)
 private:
  inline void set_has_speed();
  inline void clear_has_speed();
  inline void set_has_forced();
  inline void clear_has_forced();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  double speed_;
  bool forced_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_messages_5finternal_5fcommand_2eproto();
  friend void protobuf_AssignDesc_messages_5finternal_5fcommand_2eproto();
  friend void protobuf_ShutdownFile_messages_5finternal_5fcommand_2eproto();
  
  void InitAsDefaultInstance();
  static CommandDribbler* default_instance_;
};
// -------------------------------------------------------------------

class CommandRobot : public ::google::protobuf::Message {
 public:
  CommandRobot();
  virtual ~CommandRobot();
  
  CommandRobot(const CommandRobot& from);
  
  inline CommandRobot& operator=(const CommandRobot& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const CommandRobot& default_instance();
  
  void Swap(CommandRobot* other);
  
  // implements Message ----------------------------------------------
  
  CommandRobot* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CommandRobot& from);
  void MergeFrom(const CommandRobot& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required uint32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);
  
  // repeated .CommandWheel wheels = 2;
  inline int wheels_size() const;
  inline void clear_wheels();
  static const int kWheelsFieldNumber = 2;
  inline const ::CommandWheel& wheels(int index) const;
  inline ::CommandWheel* mutable_wheels(int index);
  inline ::CommandWheel* add_wheels();
  inline const ::google::protobuf::RepeatedPtrField< ::CommandWheel >&
      wheels() const;
  inline ::google::protobuf::RepeatedPtrField< ::CommandWheel >*
      mutable_wheels();
  
  // optional .CommandKicker kicker = 3;
  inline bool has_kicker() const;
  inline void clear_kicker();
  static const int kKickerFieldNumber = 3;
  inline const ::CommandKicker& kicker() const;
  inline ::CommandKicker* mutable_kicker();
  inline ::CommandKicker* release_kicker();
  
  // optional .CommandDribbler dribbler = 4;
  inline bool has_dribbler() const;
  inline void clear_dribbler();
  static const int kDribblerFieldNumber = 4;
  inline const ::CommandDribbler& dribbler() const;
  inline ::CommandDribbler* mutable_dribbler();
  inline ::CommandDribbler* release_dribbler();
  
  // @@protoc_insertion_point(class_scope:CommandRobot)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_kicker();
  inline void clear_has_kicker();
  inline void set_has_dribbler();
  inline void clear_has_dribbler();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::CommandWheel > wheels_;
  ::CommandKicker* kicker_;
  ::CommandDribbler* dribbler_;
  ::google::protobuf::uint32 id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_messages_5finternal_5fcommand_2eproto();
  friend void protobuf_AssignDesc_messages_5finternal_5fcommand_2eproto();
  friend void protobuf_ShutdownFile_messages_5finternal_5fcommand_2eproto();
  
  void InitAsDefaultInstance();
  static CommandRobot* default_instance_;
};
// -------------------------------------------------------------------

class ToTransmission : public ::google::protobuf::Message {
 public:
  ToTransmission();
  virtual ~ToTransmission();
  
  ToTransmission(const ToTransmission& from);
  
  inline ToTransmission& operator=(const ToTransmission& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const ToTransmission& default_instance();
  
  void Swap(ToTransmission* other);
  
  // implements Message ----------------------------------------------
  
  ToTransmission* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ToTransmission& from);
  void MergeFrom(const ToTransmission& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // repeated .CommandRobot robots = 1;
  inline int robots_size() const;
  inline void clear_robots();
  static const int kRobotsFieldNumber = 1;
  inline const ::CommandRobot& robots(int index) const;
  inline ::CommandRobot* mutable_robots(int index);
  inline ::CommandRobot* add_robots();
  inline const ::google::protobuf::RepeatedPtrField< ::CommandRobot >&
      robots() const;
  inline ::google::protobuf::RepeatedPtrField< ::CommandRobot >*
      mutable_robots();
  
  // @@protoc_insertion_point(class_scope:ToTransmission)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::CommandRobot > robots_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_messages_5finternal_5fcommand_2eproto();
  friend void protobuf_AssignDesc_messages_5finternal_5fcommand_2eproto();
  friend void protobuf_ShutdownFile_messages_5finternal_5fcommand_2eproto();
  
  void InitAsDefaultInstance();
  static ToTransmission* default_instance_;
};
// ===================================================================


// ===================================================================

// CommandWheel

// required uint32 id = 1;
inline bool CommandWheel::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CommandWheel::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CommandWheel::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CommandWheel::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 CommandWheel::id() const {
  return id_;
}
inline void CommandWheel::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required double speed = 2;
inline bool CommandWheel::has_speed() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CommandWheel::set_has_speed() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CommandWheel::clear_has_speed() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CommandWheel::clear_speed() {
  speed_ = 0;
  clear_has_speed();
}
inline double CommandWheel::speed() const {
  return speed_;
}
inline void CommandWheel::set_speed(double value) {
  set_has_speed();
  speed_ = value;
}

// -------------------------------------------------------------------

// CommandKicker

// required double speed = 1;
inline bool CommandKicker::has_speed() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CommandKicker::set_has_speed() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CommandKicker::clear_has_speed() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CommandKicker::clear_speed() {
  speed_ = 0;
  clear_has_speed();
}
inline double CommandKicker::speed() const {
  return speed_;
}
inline void CommandKicker::set_speed(double value) {
  set_has_speed();
  speed_ = value;
}

// optional bool forced = 2 [default = false];
inline bool CommandKicker::has_forced() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CommandKicker::set_has_forced() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CommandKicker::clear_has_forced() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CommandKicker::clear_forced() {
  forced_ = false;
  clear_has_forced();
}
inline bool CommandKicker::forced() const {
  return forced_;
}
inline void CommandKicker::set_forced(bool value) {
  set_has_forced();
  forced_ = value;
}

// -------------------------------------------------------------------

// CommandDribbler

// required double speed = 1;
inline bool CommandDribbler::has_speed() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CommandDribbler::set_has_speed() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CommandDribbler::clear_has_speed() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CommandDribbler::clear_speed() {
  speed_ = 0;
  clear_has_speed();
}
inline double CommandDribbler::speed() const {
  return speed_;
}
inline void CommandDribbler::set_speed(double value) {
  set_has_speed();
  speed_ = value;
}

// optional bool forced = 2 [default = false];
inline bool CommandDribbler::has_forced() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CommandDribbler::set_has_forced() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CommandDribbler::clear_has_forced() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CommandDribbler::clear_forced() {
  forced_ = false;
  clear_has_forced();
}
inline bool CommandDribbler::forced() const {
  return forced_;
}
inline void CommandDribbler::set_forced(bool value) {
  set_has_forced();
  forced_ = value;
}

// -------------------------------------------------------------------

// CommandRobot

// required uint32 id = 1;
inline bool CommandRobot::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CommandRobot::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CommandRobot::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CommandRobot::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 CommandRobot::id() const {
  return id_;
}
inline void CommandRobot::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// repeated .CommandWheel wheels = 2;
inline int CommandRobot::wheels_size() const {
  return wheels_.size();
}
inline void CommandRobot::clear_wheels() {
  wheels_.Clear();
}
inline const ::CommandWheel& CommandRobot::wheels(int index) const {
  return wheels_.Get(index);
}
inline ::CommandWheel* CommandRobot::mutable_wheels(int index) {
  return wheels_.Mutable(index);
}
inline ::CommandWheel* CommandRobot::add_wheels() {
  return wheels_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CommandWheel >&
CommandRobot::wheels() const {
  return wheels_;
}
inline ::google::protobuf::RepeatedPtrField< ::CommandWheel >*
CommandRobot::mutable_wheels() {
  return &wheels_;
}

// optional .CommandKicker kicker = 3;
inline bool CommandRobot::has_kicker() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void CommandRobot::set_has_kicker() {
  _has_bits_[0] |= 0x00000004u;
}
inline void CommandRobot::clear_has_kicker() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void CommandRobot::clear_kicker() {
  if (kicker_ != NULL) kicker_->::CommandKicker::Clear();
  clear_has_kicker();
}
inline const ::CommandKicker& CommandRobot::kicker() const {
  return kicker_ != NULL ? *kicker_ : *default_instance_->kicker_;
}
inline ::CommandKicker* CommandRobot::mutable_kicker() {
  set_has_kicker();
  if (kicker_ == NULL) kicker_ = new ::CommandKicker;
  return kicker_;
}
inline ::CommandKicker* CommandRobot::release_kicker() {
  clear_has_kicker();
  ::CommandKicker* temp = kicker_;
  kicker_ = NULL;
  return temp;
}

// optional .CommandDribbler dribbler = 4;
inline bool CommandRobot::has_dribbler() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void CommandRobot::set_has_dribbler() {
  _has_bits_[0] |= 0x00000008u;
}
inline void CommandRobot::clear_has_dribbler() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void CommandRobot::clear_dribbler() {
  if (dribbler_ != NULL) dribbler_->::CommandDribbler::Clear();
  clear_has_dribbler();
}
inline const ::CommandDribbler& CommandRobot::dribbler() const {
  return dribbler_ != NULL ? *dribbler_ : *default_instance_->dribbler_;
}
inline ::CommandDribbler* CommandRobot::mutable_dribbler() {
  set_has_dribbler();
  if (dribbler_ == NULL) dribbler_ = new ::CommandDribbler;
  return dribbler_;
}
inline ::CommandDribbler* CommandRobot::release_dribbler() {
  clear_has_dribbler();
  ::CommandDribbler* temp = dribbler_;
  dribbler_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// ToTransmission

// repeated .CommandRobot robots = 1;
inline int ToTransmission::robots_size() const {
  return robots_.size();
}
inline void ToTransmission::clear_robots() {
  robots_.Clear();
}
inline const ::CommandRobot& ToTransmission::robots(int index) const {
  return robots_.Get(index);
}
inline ::CommandRobot* ToTransmission::mutable_robots(int index) {
  return robots_.Mutable(index);
}
inline ::CommandRobot* ToTransmission::add_robots() {
  return robots_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::CommandRobot >&
ToTransmission::robots() const {
  return robots_;
}
inline ::google::protobuf::RepeatedPtrField< ::CommandRobot >*
ToTransmission::mutable_robots() {
  return &robots_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_messages_5finternal_5fcommand_2eproto__INCLUDED