package scala.scalanative.build

object Platform {

  case class UnsupportedOSError(msg: String) extends UnsupportedOperationException

  sealed abstract class OS
  case class Unix() extends OS
  case class Win() extends OS

  object OS {
    def apply(): OS = {
      val osName = System.getProperty("os.name")
      osName.toLowerCase.split(" ").headOption match {
        case Some("linux") | Some("mac") => Unix()
        case Some("windows") => Win()
        case Some(os) => throw UnsupportedOSError(s"Unknown OS: $os")
        case None => throw UnsupportedOSError("Could not detect OS")
      }
    }
  }

  final private val SUPPORTED_UNIX_NATIVE_LIBS = Set(
    "org.scala-native:clib",
    "org.scala-native:nativelib",
    "org.scala-native:posixlib",
  )

  final private val SUPPORTED_WIN_NATIVE_LIBS = Set(
    "org.scala-native:clib",
    "org.scala-native:nativelib",
    "org.scala-native:windowslib",
  )

  def nativeLibIsSupported(lib: String): Boolean = {
    OS() match {
      case Unix() =>
        SUPPORTED_UNIX_NATIVE_LIBS.contains(lib)
      case Win() =>
        SUPPORTED_WIN_NATIVE_LIBS.contains(lib)
    }
  }

  def which: String = {
    OS() match {
      case Unix() => "which"
      case Win() => "where.exe"
    }
  }

  def command(cmd: Seq[String]): Seq[String] = {
    OS() match {
      case Unix() =>
        cmd
      case Win() =>
        Seq("cmd", "/c") ++ cmd
    }
  }

  def globifyPathStr(path: String): String = {
    OS() match {
      case Unix() =>
        path
      case Win() =>
        path.replace("\\", "\\\\")
    }
  }

}
