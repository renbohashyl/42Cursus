import { useRouter } from "next/router"
import { useEffect } from "react";

export default function EndPoint() {

  const router = useRouter();

  useEffect(() => {
    router.replace("/main");
  }, [])

  return (
    <>
    </>
  )
}
