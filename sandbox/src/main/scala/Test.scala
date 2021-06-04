import scala.scalanative.posix.pthread.{pthread_join, pthread_self}
import scala.scalanative.posix.sys.types.pthread_t
import scala.scalanative.runtime.IsolateLayer.new_isolate
import scala.scalanative.unsafe.{CFuncPtr1, Ptr, stackalloc}

object Test {
  def main(args: Array[String]): Unit = {
    println("Hello, world!")
    f()
  }

  def sayHello(arg: Ptr[Byte]): Ptr[Byte] = {
    val tid = pthread_self()
    println(s"Hello, world from isolate! [tid = $tid]")
    null
  }

  def f(): Unit = {
    val tid = stackalloc[pthread_t]
    new_isolate(tid, CFuncPtr1.fromScalaFunction(sayHello), tid.asInstanceOf[Ptr[Byte]])
    println(s"Created isolate with tid = ${!tid}")
    pthread_join(!tid, null)
  }
}
