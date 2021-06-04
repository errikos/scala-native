package scala.scalanative.runtime

import scala.scalanative.posix.sys.types.pthread_t
import scala.scalanative.unsafe._

@link("pthread")
@extern
object IsolateLayer {

  def new_isolate(tid: Ptr[pthread_t], f: CFuncPtr1[Ptr[Byte], Ptr[Byte]], f_arg: Ptr[Byte]): CInt = extern

}
